#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <vector>
#include <iostream>

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        void addElement(int element);
        void removeElement(int element);
        bool getElement(int element) const;
        int size() const;

        // classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        MagicalContainer &container;
        std::vector<int>::iterator iterator;

    public:
        AscendingIterator(MagicalContainer &container);
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        int operator*() const;
        AscendingIterator &operator=(const AscendingIterator &other);
        AscendingIterator &operator++();
        AscendingIterator begin() const;
        AscendingIterator end() const;
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &container;
        std::vector<int>::iterator forwardIterator;
        std::vector<int>::iterator backwardIterator;
        bool isBackwards;

    public:
        SideCrossIterator(MagicalContainer &container);
        SideCrossIterator(MagicalContainer &, std::vector<int>::iterator, std::vector<int>::iterator, bool);
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
        MagicalContainer &container;
        std::vector<int>::const_iterator iterator;
        bool isPrime(int number) const;

    public:
        PrimeIterator(MagicalContainer &container);
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        int operator*() const;
        PrimeIterator &operator=(const PrimeIterator &other);
        PrimeIterator &operator++();
        PrimeIterator begin() const;
        PrimeIterator end() const;
    };

}
#endif