#pragma once

#include <libds/amt/implicit_sequence.h>
#include <libds/adt/queue.h>
#include <libds/adt/array.h>
#include <functional>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace ds::adt
{
    template <typename T>
    struct Sort
    {
    public:
        virtual void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) = 0;
        void sort(amt::ImplicitSequence<T>& is) { sort(is, [](const T& a, const T& b)->bool {return a < b; }); }
    };

    //----------

    template <typename T>
    class SelectSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class InsertSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class BubbleSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class QuickSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max);
    };

    //----------

    template <typename T>
    class HeapSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class ShellSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k);
    };

    //----------

    template <typename Key, typename T>
    class RadixSort :
        public Sort<T>
    {
        static_assert(std::is_integral_v<Key>, "Radix sort supports only integral types.");

    public:
        RadixSort();
        RadixSort(std::function<Key(const T&)> getKey);

        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        std::function<Key(const T&)> getKey_;
    };

    //----------

    template <typename T>
    class MergeSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void split(size_t n);
        void merge(std::function<bool(const T&, const T&)> compare, size_t n);

    private:
        ImplicitQueue<T>* queue1_ {nullptr};
        ImplicitQueue<T>* queue2_ {nullptr};
        ImplicitQueue<T>* mergeQueue_ {nullptr};
    };

    //----------

    template<typename T>
    void SelectSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        for (size_t i = 0; i < is.size() - 1; ++i)
        {
            size_t minIndex = i;
            for (size_t j = i + 1; j < is.size(); ++j)
            {
                if (compare(is.access(j)->data_, is.access(minIndex)->data_))
                {
                    minIndex = j;
                }
            }
            std::swap(is.access(i)->data_, is.access(minIndex)->data_); 
        }
    }

    template<typename T>
    void InsertSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        for (int i = 1; i <= is.size() - 1; ++i)
        {
            T tmp = is.access(i)->data_;
            int j = i;
            while (j > 0 && compare(tmp, is.access(j - 1)->data_))
            {
                is.access(j)->data_ = is.access(j - 1)->data_;
                --j;
            }
            is.access(j)->data_ = tmp;
        }
    }

    template<typename T>
    void BubbleSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        bool vymena;
        do
        {
            vymena = false;
            for (int i = 0; i < is.size() - 1; ++i)
            {
                if (compare(is.access(i+1)->data_, is.access(i)->data_))
                {
                    std::swap(is.access(i+1)->data_, is.access(i)->data_);
                    vymena = true;
                }
            }
        } while (vymena);
    }

    template<typename T>
    void QuickSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        if (!is.isEmpty())
        {
            quick(is, compare, 0, is.size() - 1);
        }
    }

    template<typename T>
    void QuickSort<T>::quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        T pivot = is.access(min + (max - min) / 2)->data_;
        int lavy = min;
        int pravy = max;

        do
        {
            while (compare(is.access(lavy)->data_, pivot))
            {
                ++lavy;
            }
            while (pravy > 0 && compare(pivot, is.access(pravy)->data_))
            {
                --pravy;
            }
            if (lavy <= pravy)
            {
                std::swap(is.access(lavy)->data_, is.access(pravy)->data_);
                ++lavy;
                if (pravy > 0)
                {
                    --pravy;
                }
            }
        } while (lavy <= pravy);

        if (min < pravy)
        {
            quick(is, compare, min, pravy);
        }
        if (lavy < max)
        {
            quick(is, compare, lavy, max);
        }
    }

    template<typename T>
    void HeapSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        for (int i = 1; i <= is.size() - 1; ++i)
        {
            bool vymena;
            int aktualny = i;
            do
            {
                vymena = false;
                int otec = (aktualny - 1) / 2;
                if (aktualny > 0 && compare(is.access(otec)->data_, is.access(aktualny)->data_))
                {
                    std::swap(is.access(aktualny)->data_, is.access(otec)->data_);
                    aktualny = otec;
                    vymena = true;
                }
            } while (vymena);
        }
        for (int i = is.size() - 1; i >= 1; --i)
        {
            std::swap(is.access(0)->data_, is.access(i)->data_);
            bool vymena;
            int aktualny = 0;
            do
            {
                vymena = false;
                int lavy = 2 * aktualny + 1;
                int pravy = 2 * aktualny + 2;
                int max;
                if (lavy < i && pravy < i)
                {
                    max = compare(is.access(pravy)->data_, is.access(lavy)->data_) ? lavy : pravy;
                }
                else
                {
                    max = (lavy < i) ? lavy : pravy;
                }
                if (max < i && compare(is.access(aktualny)->data_, is.access(max)->data_))
                {
                    std::swap(is.access(aktualny)->data_, is.access(max)->data_);
                    aktualny = max;
                    vymena = true;
                }
            } while (vymena);
        }
    }

    template<typename T>
    void ShellSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        shell(is, compare, static_cast<size_t>(std::ceil(std::log10(is.size()))));
    }

    template<typename T>
    void ShellSort<T>::shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        for (int d = 0; d < k; ++d)
        {
            for (int i = d; i < is.size(); ++i)
            {
                int j = i;
                while (j >= k && (j - k) >= d && compare(is.access(j)->data_, is.access(j - k)->data_))
                {
                    std::swap(is.access(j)->data_, is.access(j - k)->data_);
                    j = j - k;
                }
            }
        }
        if (k > 1)
        {
            this->shell(is, compare, k - 1);
        }
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort() :
        getKey_([](auto const& x) { return x; })
    {
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort(std::function<Key(const T&)> getKey) :
        getKey_(getKey)
    {
    }

    template<typename Key, typename T>
    void RadixSort<Key, T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::split(size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::merge(std::function<bool(const T&, const T&)> compare, size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }
}