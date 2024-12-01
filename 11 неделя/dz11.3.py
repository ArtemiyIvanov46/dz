%%unittest_main
class TestOrdinaryList(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(fastsort1('1 2 3 4'),'1 2 3 4' , "should be 1 2 3 4")

class TestEmptyList(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(fastsort1(''), 'Nothing', "should be Nothing")

class TestListOfZeros(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(fastsort1('0 0 0'),'0 0 0', "should be 0 0 0")

class TestListWithNegatives(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(fastsort1('-1 -2 2 3'), '-2 -1 2 3', "should be -2 -1 2 3")

class TestAlwaysFAIL(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(fastsort1('1 11 9 13'), '1 9 11 13', "should be 1 9 11 13")