

#include "Package.hh"


namespace oct::pkmt::v0
{
    void print(std::ostream& out,Package const& pack, size_t margin)
    {
        std::string strmargin;
        strmargin.insert(0,margin,'\t');
        out << strmargin << pack->name << "\n";
        for(size_t i = 0; i < pack.size(); i++)
        {
            print(out,pack[i],margin + 1);
        }
    }
}
