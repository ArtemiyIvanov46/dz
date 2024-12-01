%%unittest_main
class TestOrdinarynumber(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(mnk([1,2],[1,2]), '(1, 0)', "should be (1, 0)")

class Teststepen(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(mnk([3,2],[2,1]),'(1, 1)' , "should be (1, 1)")

class TestOfZeros(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(mnk([0],[0]),'(nan, nan)', "should be (nan, nan)")

class TestListWithNegatives(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(mnk([],[]), '(nan, nan)', "should be (nan, nan)")

class complextext(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(mnk([0, 1.0506, 4.2025, 9.456, 16.81, 26.27, 37.8225, 51.48],[0.00938, 0.00949, 0.00963, 0.00975, 0.00995, 0.0101, 0.01046, 0.01084]), 'should be (2.659e-05, 0.009461)', "should be 2.659e-05, 0.009461")