#include "MagicalContainer.hpp"
#include <iostream>
#include <algorithm>

namespace ariel
{
    // My shorcut
    typedef MagicalContainer::AscendingIterator short_Asc;
    typedef MagicalContainer::SideCrossIterator short_Sid;
    typedef MagicalContainer::PrimeIterator short_Pri;

    void MagicalContainer::addElement(int element)
    {
        elements.push_back(element);
    }

    void MagicalContainer::removeElement(int element)
    {
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    }

    size_t MagicalContainer::size() const
    {
        return elements.size();
    }

    void MagicalContainer::print() const
    {
        std::cout << "Container elements: ";
        for (const auto &element : elements)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    const std::vector<int> &MagicalContainer::getElements() const
    {
        return elements;
    }

    bool MagicalContainer::isPrime(int num) const
    {
        if (num < 2)
        {
            return false;
        }
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    short_Asc::AscendingIterator(const MagicalContainer &cont) : container(cont), sortedElements(container.getElements()), index(0)
    {
        std::sort(sortedElements.begin(), sortedElements.end());
    }

    bool short_Asc::operator==(const AscendingIterator &other) const
    {
        return &container == &other.container && index == other.index;
    }

    bool short_Asc::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool short_Asc::operator>(const AscendingIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Comparison between iterators of different containers.");
        }
        return index > other.index;
    }

    bool short_Asc::operator<(const AscendingIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Comparison between iterators of different containers.");
        }
        return index < other.index;
    }

    int short_Asc::operator*() const
    {
        return sortedElements[index];
    }

    short_Asc &short_Asc::operator++()
    {
        ++index;
        return *this;
    }

    short_Asc &short_Asc::operator=(const AscendingIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        if (this != &other)
        {
            index = other.index;
        }
        return *this;
    }

    short_Asc short_Asc::begin() const
    {
        return AscendingIterator(container);
    }

    short_Asc short_Asc::end() const
    {
        AscendingIterator iter(container);
        iter.index = sortedElements.size(); // Point to one position past the last element
        return iter;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container)
    {
        if (container.elements.empty())
        {
            lowIterator = container.elements.end();
            highIterator = container.elements.end();
            reverse = false;
        }
        else
        {
            lowIterator = container.elements.begin();
            highIterator = std::prev(container.elements.end());
            reverse = true;
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, std::vector<int>::iterator iteratorStart, std::vector<int>::iterator iteratorEnd, bool reverse)
        : container(container), lowIterator(iteratorStart), highIterator(iteratorEnd), reverse(reverse)
    {
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {

        return (this->lowIterator == other.lowIterator) && (this->highIterator == other.highIterator) && (this->reverse == other.reverse);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {

        if (lowIterator == container.elements.end())
        {
            throw std::runtime_error("Iterator is already at the end");
        }
        if (this->lowIterator == this->highIterator)
        {
            this->lowIterator = this->container.elements.end();
            this->highIterator = this->container.elements.end();
            this->reverse = false;
            return *this;
        }

        if (reverse)
            ++this->lowIterator;
        else
            --this->highIterator;

        this->reverse = !this->reverse;
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*()
    {
        if (reverse)
            return *this->lowIterator;
        else
            return *this->highIterator;
    }

    bool MagicalContainer::MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return *lowIterator < *other.lowIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return *lowIterator > *other.lowIterator;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        if (this != &other)
        {
            container = other.container;
            lowIterator = other.lowIterator;
            highIterator = other.highIterator;
            reverse = other.reverse;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {

        if (container.elements.empty())
        {
            return end();
        }

        return SideCrossIterator(container, container.elements.begin(), std::prev(container.elements.end()), true);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(container, container.elements.end(), container.elements.end(), false);
    }

    short_Pri::PrimeIterator(const MagicalContainer &cont) : container(cont), index(0)
    {
        const std::vector<int> &elements = container.getElements();
        for (int num : elements)
        {
            if (isPrime(num))
            {
                primeElements.push_back(num);
            }
        }
        std::sort(primeElements.begin(), primeElements.end());
    }

    bool short_Pri::operator==(const PrimeIterator &other) const
    {
        return &container == &other.container && index == other.index;
    }

    bool short_Pri::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool short_Pri::operator>(const PrimeIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Comparison between iterators of different containers.");
        }
        return index > other.index;
    }

    bool short_Pri::operator<(const PrimeIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Comparison between iterators of different containers.");
        }
        return index < other.index;
    }

    int short_Pri::operator*() const
    {
        return primeElements[index];
    }

    short_Pri &short_Pri::operator++()
    {
        ++index;
        return *this;
    }

    short_Pri short_Pri::begin() const
    {
        return PrimeIterator(container);
    }

    short_Pri short_Pri::end() const
    {
        PrimeIterator iter(container);
        iter.index = primeElements.size(); // Point to one position past the last element
        return iter;
    }

    short_Pri &short_Pri::operator=(const PrimeIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        if (this != &other)
        {
            index = other.index;
        }
        return *this;
    }

    bool short_Pri::isPrime(int num)
    {
        if (num < 2)
        {
            return false;
        }
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}
