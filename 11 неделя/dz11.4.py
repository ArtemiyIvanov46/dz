%%unittest_main
class TestOrdinarytext(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.encode("гойда"), "ёсмжг", "should be ёсмжг")

class Teststepen(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.encode("гойда123"),"ёсмжг123", "should be ёсмжг123")

class TestOfZeros(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.encode("ГОЙДА"),"ЁСМЖГ", "should be ЁСМЖГ")

class TestListWithNegatives(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.encode(""), "", "should be ")

class обратные(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.decode("ёсмжг"), "гойда", "should be гойда")

class обратные(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.decode("ЁСМЖГ"), "ГОЙДА", "should be ГОЙДА")

class обратные(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.decode("ёсмжг123"), "гойда123", "should be гойда123")

class обратные(unittest.TestCase):
    def test_custom_sum(self):
        self.assertEqual(self.cipher.decode(""), "", "should be ")