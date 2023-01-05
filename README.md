# WorldCup-tests
צריך להוסיף לwet2util פונקציות השוואה:





     bool operator==(const permutation_t &rhs) const {
        for (int i = 0; i < N; ++i) {
            if(this->a[i] != rhs.a[i])
                return false;
        }
        return true;
    }

    bool operator!=(const permutation_t &rhs) const {
        return !(rhs == *this);
    }
