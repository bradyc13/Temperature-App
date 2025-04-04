/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include <lib/format/FlatTree.h>
#include <lib/format/FlatTreePosition.h>

#include <lib/core/TLVTags.h>
#include <lib/support/UnitTestRegistration.h>

#include <array>
#include <vector>

#include <string.h>

#include <nlunit-test.h>

namespace {

using namespace chip::FlatTree;
using namespace chip::TLV;

struct NamedTag
{
    Tag tag;
    const char * name;
};

/// Tree definition for
///
/// |- hello     (1)
/// \- world     (2)
///    |- a      (123, 1)
///    |- b      (234, 2)
///    |  \- foo (A)
///    \- c      (345, 3)
///
Entry<NamedTag> node1[] = {
    { { ContextTag(1), "hello" }, kInvalidNodeIndex },
    { { ContextTag(2), "world" }, 1 },
};

Entry<NamedTag> node2[] = {
    { { ProfileTag(123, 1), "a" }, kInvalidNodeIndex },
    { { ProfileTag(234, 2), "b" }, 2 },
    { { ProfileTag(345, 3), "c" }, kInvalidNodeIndex },
};

Entry<NamedTag> node3[] = {
    { { AnonymousTag(), "foo" }, kInvalidNodeIndex },
};

#define _ENTRY(n)                                                                                                                  \
    {                                                                                                                              \
        sizeof(n) / sizeof(n[0]), n                                                                                                \
    }

std::array<Node<NamedTag>, 3> tree = { {
    _ENTRY(node1),
    _ENTRY(node2),
    _ENTRY(node3),
} };

class ByTag
{
public:
    constexpr ByTag(Tag tag) : mTag(tag) {}
    bool operator()(const NamedTag & item) { return item.tag == mTag; }

private:
    const Tag mTag;
};

class ByName
{
public:
    constexpr ByName(const char * name) : mName(name) {}
    bool operator()(const NamedTag & item) { return strcmp(item.name, mName) == 0; }

private:
    const char * mName;
};

#define ASSERT_HAS_NAME(p, n)                                                                                                      \
    NL_TEST_ASSERT(inSuite, p.Get() != nullptr);                                                                                   \
    NL_TEST_ASSERT(inSuite, strcmp(p.Get()->name, n) == 0)

#define ASSERT_HAS_CONTEXT_TAG(p, t)                                                                                               \
    NL_TEST_ASSERT(inSuite, p.Get() != nullptr);                                                                                   \
    NL_TEST_ASSERT(inSuite, p.Get()->tag == ContextTag(t))

#define ASSERT_HAS_PROFILE_TAG(p, a, b)                                                                                            \
    NL_TEST_ASSERT(inSuite, p.Get() != nullptr);                                                                                   \
    NL_TEST_ASSERT(inSuite, p.Get()->tag == ProfileTag(a, b))

template <size_t N>
std::vector<Tag> GetPath(Position<NamedTag, N> & position)
{
    std::vector<Tag> result;

    for (const auto & item : position.CurrentPath())
    {
        result.push_back(item->data.tag);
    }

    return result;
}

bool HasPath(const std::vector<Tag> & v, Tag a)
{
    return (v.size() == 1) && (v[0] == a);
}

bool HasPath(const std::vector<Tag> & v, Tag a, Tag b)
{
    return (v.size() == 2) && (v[0] == a) && (v[1] == b);
}

bool HasPath(const std::vector<Tag> & v, Tag a, Tag b, Tag c)
{
    return (v.size() == 3) && (v[0] == a) && (v[1] == b) && (v[2] == c);
}

void TestSimpleEnterExit(nlTestSuite * inSuite, void * inContext)
{
    Position<NamedTag, 10> position(tree.data(), tree.size());

    // at start, top of tree has no value
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    NL_TEST_ASSERT(inSuite, GetPath(position).empty());

    // Go to hello, try going to invalid 2x, then go back
    position.Enter(ByTag(ContextTag(1)));
    ASSERT_HAS_NAME(position, "hello");
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(1)));

    position.Enter(ByTag(ContextTag(1)));
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    NL_TEST_ASSERT(inSuite, GetPath(position).empty());
    position.Enter(ByTag(ContextTag(1)));
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    position.Exit();
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    position.Exit();
    NL_TEST_ASSERT(inSuite, position.Get() != nullptr);
    ASSERT_HAS_NAME(position, "hello");
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(1)));
    position.Exit();
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
}

void TestDeeperEnter(nlTestSuite * inSuite, void * inContext)
{
    Position<NamedTag, 10> position(tree.data(), tree.size());

    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);

    position.Enter(ByName("world"));
    ASSERT_HAS_CONTEXT_TAG(position, 2);
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2)));

    position.Enter(ByTag(ProfileTag(123, 1)));
    ASSERT_HAS_NAME(position, "a");
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(123, 1)));

    position.Enter(ByTag(AnonymousTag()));
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    NL_TEST_ASSERT(inSuite, GetPath(position).empty());
    position.Exit();
    ASSERT_HAS_NAME(position, "a");
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(123, 1)));

    position.Exit();
    ASSERT_HAS_NAME(position, "world");

    position.Enter(ByName("b"));
    ASSERT_HAS_PROFILE_TAG(position, 234, 2);

    position.Enter(ByTag(AnonymousTag()));
    ASSERT_HAS_NAME(position, "foo");
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(234, 2), AnonymousTag()));

    // test some unknown
    for (int i = 0; i < 100; i++)
    {
        position.Enter(ByTag(AnonymousTag()));
        NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
        NL_TEST_ASSERT(inSuite, GetPath(position).empty());
    }
    for (int i = 0; i < 100; i++)
    {
        NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
        NL_TEST_ASSERT(inSuite, GetPath(position).empty());
        position.Exit();
    }
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(234, 2), AnonymousTag()));
    ASSERT_HAS_NAME(position, "foo");
    position.Exit();

    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(234, 2)));
    ASSERT_HAS_NAME(position, "b");
    position.Exit();

    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2)));
    ASSERT_HAS_NAME(position, "world");

    // root and stay there
    position.Exit();
    position.Exit();
    position.Exit();
    position.Exit();
    NL_TEST_ASSERT(inSuite, GetPath(position).empty());

    // can still navigate from the root
    position.Enter(ByName("world"));
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2)));
    ASSERT_HAS_CONTEXT_TAG(position, 2);
}

void TestDescendLimit(nlTestSuite * inSuite, void * inContext)
{
    Position<NamedTag, 2> position(tree.data(), tree.size());

    position.Enter(ByName("world"));
    ASSERT_HAS_CONTEXT_TAG(position, 2);

    position.Enter(ByName("b"));
    ASSERT_HAS_PROFILE_TAG(position, 234, 2);

    // only 2 positions can be remembered. Running out of space
    position.Enter(ByName("foo"));
    NL_TEST_ASSERT(inSuite, position.Get() == nullptr);
    NL_TEST_ASSERT(inSuite, GetPath(position).empty());

    position.Exit();
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2), ProfileTag(234, 2)));
    ASSERT_HAS_NAME(position, "b");
    ASSERT_HAS_PROFILE_TAG(position, 234, 2);

    position.Exit();
    NL_TEST_ASSERT(inSuite, HasPath(GetPath(position), ContextTag(2)));
    ASSERT_HAS_NAME(position, "world");
    ASSERT_HAS_CONTEXT_TAG(position, 2);
}

const nlTest sTests[] = {
    NL_TEST_DEF("TestSimpleEnterExit", TestSimpleEnterExit), //
    NL_TEST_DEF("TestDeeperEnter", TestDeeperEnter),         //
    NL_TEST_DEF("TestDescendLimit", TestDescendLimit),       //
    NL_TEST_SENTINEL()                                       //
};

} // namespace

int TestFlatTreePosition()
{
    nlTestSuite theSuite = { "FlatTree", sTests, nullptr, nullptr };
    nlTestRunner(&theSuite, nullptr);
    return nlTestRunnerStats(&theSuite);
}

CHIP_REGISTER_TEST_SUITE(TestFlatTreePosition)
