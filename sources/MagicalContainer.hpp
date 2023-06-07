#ifndef MagicalContainer_hpp
#define MagicalContainer_hpp

#include <vector>

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        void addElement(int element);
        void removeElement(int element);
        std::size_t size() const;
        void print() const;
        const std::vector<int> &getElements() const;
        bool isPrime(int num) const;

        // classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        const MagicalContainer &container;
        std::vector<int> sortedElements;
        std::size_t index;

    public:
        AscendingIterator(const MagicalContainer &container);
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        AscendingIterator &operator=(const AscendingIterator &other);
        int operator*() const;
        AscendingIterator &operator++();
        AscendingIterator begin() const;
        AscendingIterator end() const;
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &container;
        std::vector<int>::iterator lowIterator;
        std::vector<int>::iterator highIterator;
        bool reverse;

    public:
        SideCrossIterator(MagicalContainer &container);
        SideCrossIterator(MagicalContainer &container, std::vector<int>::iterator, std::vector<int>::iterator, bool reverse);
        SideCrossIterator &operator++();
        int operator*();
        bool operator==(const SideCrossIterator &) const;
        bool operator!=(const SideCrossIterator &) const;
        bool operator<(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        const MagicalContainer &container;
        std::vector<int> primeElements;
        std::size_t index;

    public:
        PrimeIterator(const MagicalContainer &container);
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        int operator*() const;
        PrimeIterator &operator++();
        PrimeIterator begin() const;
        PrimeIterator end() const;
        bool isPrime(int num);
        PrimeIterator &operator=(const PrimeIterator &other);
    };
}

#endif
