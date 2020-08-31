//
// Created by fulva on 2020/8/31.
//

#ifndef F446ZE_LINEARDIVIDER_H
#define F446ZE_LINEARDIVIDER_H

class LinearDivider {
public:
    LinearDivider(double startpoint, double endpoint, int resolution)
            : resolution(resolution), startpoint(startpoint), endpoint(endpoint) {

    }

    class DividerIterator {
    public:
        DividerIterator(LinearDivider &linearDivider, int index) : linearDivider(linearDivider), index(index) {

        }

        bool operator==(const DividerIterator &rhs) const {
            return this->index == rhs.index;
        }

        bool operator!=(const DividerIterator &rhs) const {
            return !(*this == rhs);
        }

        DividerIterator &operator++() {
            ++index;
            return *this;
        }

        double operator*() {

            return linearDivider.startpoint +
                   (linearDivider.endpoint - linearDivider.startpoint) * (index / linearDivider.resolution);
        }


    private:
        LinearDivider &linearDivider;
        int index;
    };

    DividerIterator begin() {
        return {*this, 0};
    }

    DividerIterator end() {
        return {*this, resolution};
    }

private:
    double startpoint;
    double endpoint;
    int resolution;
};


#endif //F446ZE_LINEARDIVIDER_H
