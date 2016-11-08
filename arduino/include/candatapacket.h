#ifndef TJLUTILS_CANDATAPACKET_H
#define TJLUTILS_CANDATAPACKET_H

#include <string>
#include <vector>
#include <iostream>


class CanDataPacket
{
public:
    CanDataPacket();
    CanDataPacket(const std::vector<unsigned char> &packet);
    CanDataPacket(unsigned char first, unsigned char second, 
                  unsigned char third, unsigned char fourth, 
                  unsigned char fifth, unsigned char sixth, 
                  unsigned char seventh, unsigned char eighth);
    CanDataPacket(const CanDataPacket &dataPacket);                  
    void setDataPacket(const std::vector<unsigned char> &dataPacket);

    void setDataPacket(unsigned char first, unsigned char second, 
                       unsigned char third, unsigned char fourth, 
                       unsigned char fifth, unsigned char sixth, 
                       unsigned char seventh, unsigned char eighth);
    bool setNthByte(int index, unsigned char nth);
    void toBasicArray(unsigned char copyArray[8]) const;
    unsigned char nthByte(int index);
    std::vector<unsigned char> dataPacket() const;

    friend bool operator==(const CanDataPacket &lhs, const CanDataPacket &rhs) 
    {
        if (lhs.dataPacket().size() != rhs.dataPacket().size()) {
            return false;
        }
        int i{0};
        for (auto &it : rhs.dataPacket()) {
            if (it != rhs.dataPacket().at(i++)) {
                return false;
            }
        }
        return true;
    }

    static CanDataPacket combineDataPackets(const CanDataPacket &first, const CanDataPacket &second);

private:
    std::vector<unsigned char> m_dataPacket;
};

#endif //TJLUTILS_CANDATAPACKET_H
