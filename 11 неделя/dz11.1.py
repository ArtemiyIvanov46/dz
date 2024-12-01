%%unittest_main
class TestOrdinarynumber(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(factor(14), [2,7], "should be 2,7")

class Teststepen(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(factor(128), [2,2,2,2,2,2,2], "should be 2,2,2,2,2,2,2")

class TestOfZeros(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(factor(0),[0], "should be 0")

class TestListWithNegatives(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(factor(-5), [-5], "should be -5")

class complextext(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(factor(78968923),[11, 151, 47543] , "should be error")
