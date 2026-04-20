#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class IntrusionDetector
{
private:
    unsigned short int timeThreshold = 0;
    unsigned short int portLimit = 0;

    std::map<std::string, std::vector<std::pair<unsigned long long, unsigned short int>>> history;

public:
    void setTimeThreshold(unsigned short int timeThreshold) {
        this->timeThreshold = timeThreshold;
    }

    void setPortLimit(unsigned short int portLimit) {
        this->portLimit = portLimit;
    }

    void handleConnection(const Connection& c) {
        history[c.getSource()].push_back({c.getTimestamp(), c.getPort()});
    }

    bool isIntruder(const std::string& source) const {
        auto it = history.find(source);
        if (it == history.end()) {
            return false;
        }

        std::vector<std::pair<unsigned long long, unsigned short int>> v = it->second;
        std::sort(v.begin(), v.end());

        int n = (int)v.size();

        for (int i = 0; i < n; ++i) {
            std::set<unsigned short int> ports;

            for (int j = i; j < n; ++j) {
                if (v[j].first - v[i].first >= timeThreshold) {
                    break;
                }

                ports.insert(v[j].second);

                if ((int)ports.size() >= portLimit) {
                    return true;
                }
            }
        }

        return false;
    }
};
