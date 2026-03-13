#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<unsigned char> rc4(const string& key, const vector<unsigned char>& data)
{
    vector<int> S(256);
    for (int i = 0; i < 256; i++)
        S[i] = i;

    int j = 0;

    // KSA
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        swap(S[i], S[j]);
    }

    // PRGA
    vector<unsigned char> out(data.size());
    int i = 0;
    j = 0;

    for (size_t n = 0; n < data.size(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);

        int K = S[(S[i] + S[j]) % 256];
        out[n] = data[n] ^ K;
    }

    return out;
}

int main()
{
    string key = "oh, you think darkness is your ally";

    ifstream file("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework 2.3.3/3.bin", ios::binary);
    vector<unsigned char> data(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    vector<unsigned char> decrypted = rc4(key, data);

    cout << string(decrypted.begin(), decrypted.end()) << endl;

    return 0;
}
//You are wonderful! Great work! Do I Look Like a Guy With a Plan?
//крутое задание
