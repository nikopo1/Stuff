#ifndef _SAMPLE_H
#define _SAMPLE_H

#include <string>

class Entry {
    private:
        std::string key_;
        std::string value_;
        bool readonly_;

    public:
        // For non-mapped types
        Entry(std::string key,
                bool readonly = true);

        // For mapped types
        Entry(std::string key,
                std::string value,
                bool readonly = true);

        std::string key() const;
        std::string value() const;
        bool readonly() const;
};

#endif // _SAMPLE_H
