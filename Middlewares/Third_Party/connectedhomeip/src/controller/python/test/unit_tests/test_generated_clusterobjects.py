import unittest

import chip.clusters as Clusters
from chip.clusters.Types import NullValue
from rich.pretty import pprint

'''
This file contains tests for validating the generated cluster objects by running encoding and decoding
through them symmetrically to exercise both pathways.
'''

enable_debug = False


class TestGeneratedClusterObjects(unittest.TestCase):
    def CheckData(self, expected):
        tlv = expected.ToTLV()
        actual = expected.FromTLV(tlv)

        if (enable_debug):
            print("Expected Data:")
            pprint(expected, expand_all=True)

            print("Actual Data:")
            pprint(actual, expand_all=True)

        self.assertEqual(actual, expected)

    def test_simple_struct(self):
        data = Clusters.UnitTesting.Structs.SimpleStruct()
        data.a = 23
        data.b = True
        data.c = Clusters.UnitTesting.Enums.SimpleEnum.kValueA
        data.d = b'1234'
        data.e = 'hello'
        data.f = 1
        data.g = 0
        data.h = 0

        self.CheckData(data)

    def test_double_nested_struct_list(self):
        simpleStruct = Clusters.UnitTesting.Structs.SimpleStruct()
        simpleStruct.a = 23
        simpleStruct.b = True
        simpleStruct.c = Clusters.UnitTesting.Enums.SimpleEnum.kValueA
        simpleStruct.d = b'1234'
        simpleStruct.e = 'hello'
        simpleStruct.f = 1
        simpleStruct.g = 0
        simpleStruct.h = 0

        data = Clusters.UnitTesting.Structs.NestedStructList()
        data.a = 23
        data.b = True
        data.c = simpleStruct
        data.d = []
        data.d.append(simpleStruct)
        data.d.append(simpleStruct)

        data.e = [1, 2, 3, 4]
        data.f = [b'1', b'2', b'3']
        data.g = [2, 3, 4, 5]

        self.CheckData(data)

    def test_nullable_optional_struct(self):
        data = Clusters.UnitTesting.Structs.NullablesAndOptionalsStruct()

        data.nullableInt = 2
        data.optionalInt = 3
        data.nullableOptionalInt = 4
        data.nullableString = 'hello1'
        data.optionalString = 'hello2'
        data.nullableOptionalString = 'hello3'
        data.nullableStruct = Clusters.UnitTesting.Structs.SimpleStruct(
            23, True, Clusters.UnitTesting.Enums.SimpleEnum.kValueA, b'1234', 'hello', 1, 0, 0)
        data.optionalStruct = Clusters.UnitTesting.Structs.SimpleStruct(
            24, True, Clusters.UnitTesting.Enums.SimpleEnum.kValueA, b'1234', 'hello', 1, 0, 0)
        data.nullableOptionalStruct = Clusters.UnitTesting.Structs.SimpleStruct(
            25, True, Clusters.UnitTesting.Enums.SimpleEnum.kValueA, b'1234', 'hello', 1, 0, 0)

        data.nullableList = [Clusters.UnitTesting.Enums.SimpleEnum.kValueA]
        data.optionalList = [Clusters.UnitTesting.Enums.SimpleEnum.kValueA]
        data.nullableOptionalList = [
            Clusters.UnitTesting.Enums.SimpleEnum.kValueA]

        self.CheckData(data)

        data.nullableInt = NullValue
        data.nullableOptionalInt = NullValue
        data.nullableOptionalString = NullValue
        data.nullableStruct = NullValue
        data.nullableOptionalStruct = NullValue
        data.nullableList = NullValue
        data.nullableOptionalList = NullValue

        self.CheckData(data)

        data.nullableOptionalInt = None
        data.nullableOptionalString = None
        data.nullableOptionalStruct = None
        data.nullableOptionalList = None

        self.CheckData(data)


if __name__ == '__main__':
    unittest.main()
