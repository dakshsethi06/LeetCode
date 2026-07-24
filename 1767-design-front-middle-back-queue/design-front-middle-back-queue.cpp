class FrontMiddleBackQueue {
    deque<int> left, right;

    void rebalance() {
        while (left.size() > right.size() + 1) {
            right.push_front(left.back());
            left.pop_back();
        }

        while (left.size() < right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        left.push_front(val);
        rebalance();
    }

    void pushMiddle(int val) {
        if (left.size() > right.size()) {
            right.push_front(left.back());
            left.pop_back();
        }
        left.push_back(val);
    }

    void pushBack(int val) {
        right.push_back(val);
        rebalance();
    }

    int popFront() {
        if (left.empty()) return -1;

        int ans = left.front();
        left.pop_front();
        rebalance();
        return ans;
    }

    int popMiddle() {
        if (left.empty()) return -1;

        int ans = left.back();
        left.pop_back();
        rebalance();
        return ans;
    }

    int popBack() {
        if (left.empty()) return -1;

        int ans;
        if (!right.empty()) {
            ans = right.back();
            right.pop_back();
        } else {
            ans = left.back();
            left.pop_back();
        }

        rebalance();
        return ans;
    }
};