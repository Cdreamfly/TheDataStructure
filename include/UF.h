#pragma once

class UF {
private:
    virtual const int getSize() const noexcept = 0;

    virtual bool isConnected(int p, int q) = 0;

    virtual void unionElements(int p, int q) = 0;

    virtual ~UF() {}
};
