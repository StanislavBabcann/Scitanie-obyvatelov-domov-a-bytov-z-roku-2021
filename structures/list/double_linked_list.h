#pragma once

#include "list.h"
#include "linked_list.h"

namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.


    template<typename T>
    class DoubleLinkedListItem : public DataItem<T>
    {
    public:
        DoubleLinkedListItem(T data);


        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        ~DoubleLinkedListItem();

        DoubleLinkedListItem<T>* getNext();

        void setNext(DoubleLinkedListItem<T>* next);

        DoubleLinkedListItem<T>* getPrevious();

        void setPrevious(DoubleLinkedListItem<T>* previous);

    private:
        DoubleLinkedListItem<T>* next_;
        DoubleLinkedListItem<T>* previous_;

    };
	
    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public List<T> 
	{
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        size_t size_;
        DoubleLinkedListItem<T>* first_;
        DoubleLinkedListItem<T>* last_;

    private:
        DoubleLinkedListItem<T>* getItemAtIndex(int index);

    private:

        class DoubleLinkedListIterator : public Iterator<T>
        {
        public:
            DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

            ~DoubleLinkedListIterator();

            Iterator<T>& operator= (Iterator<T>& other) override;

            bool operator!=(Iterator<T>& other) override;

            T operator*() override;

            Iterator<T>& operator++() override;

        private:
            DoubleLinkedListItem<T>* position_;
        };
	};


    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr),
        previous_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_),
        previous_(other.previous_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        next_ = nullptr;
        previous_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
    {
        return previous_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
    {
        previous_ = previous;
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other) 
    {
        size_ = 0;
        DoubleLinkedList<T>& otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>&>(other);
        DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList.first_;
        while (otherItem != nullptr) {
            add(otherItem->accessData());
            otherItem = otherItem->getNext();
        }
        
        
        
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        if (this != &other) {
            DoubleLinkedList<T>& otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>&>(other);
            clear();
            DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList.first_;
            while (otherItem != nullptr) {
                add(otherItem->accessData());
                otherItem = otherItem->getNext();
            }
        }

        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        if (this == &other) {
            return true;
        }

        if (size_ != other.size()) {
            return false;
        }

        DoubleLinkedList<T>* otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>*>(&other);
        if (otherDoubleLinkedList == nullptr) {
            return false;
        }

        DoubleLinkedListItem<T>* item = first_;
        DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList->first_;

        while (item != nullptr) {
            if (item->accessData() != otherItem->accessData()) {
                return false;
            }
            item = item->getNext();
            otherItem = otherItem->getNext();
        }

        return true;
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index!");

        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        DoubleLinkedListItem<T>* newDoubleLinkedListItem = new DoubleLinkedListItem<T>(data);
        if (size_ == 0) {
            first_ = newDoubleLinkedListItem;
        }
        else {
            last_->setNext(newDoubleLinkedListItem);
            newDoubleLinkedListItem->setPrevious(last_);
        }
        last_ = newDoubleLinkedListItem;
        size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        if (size_ == index) {
            add(data);
        }
        else {
            Utils::rangeCheckExcept(index, size_, "Invalid index!");

            DoubleLinkedListItem<T>* newDoubleLinkedListItem = new DoubleLinkedListItem<T>(data);

            if (index == 0) {
                newDoubleLinkedListItem->setNext(first_);
                first_->setPrevious(newDoubleLinkedListItem);
                first_ = newDoubleLinkedListItem;
            }
            else {
                
                DoubleLinkedListItem<T>* previousDoubleLinkedListItem = getItemAtIndex(index - 1);
                newDoubleLinkedListItem->setNext(previousDoubleLinkedListItem->getNext());
                newDoubleLinkedListItem->setPrevious(previousDoubleLinkedListItem);

                previousDoubleLinkedListItem->getNext()->setPrevious(newDoubleLinkedListItem);
                previousDoubleLinkedListItem->setNext(newDoubleLinkedListItem);
                
            }

            size_++;
        }
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        int index = getIndexOf(data);
        if (index == -1) {
            return false;
        }
        else {
            removeAt(index);
            return true;
        }
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index!");
        DoubleLinkedListItem<T>* itemToDelete;

        if (index != 0) {
            DoubleLinkedListItem<T>* previousItem = this->getItemAtIndex(index - 1);
            itemToDelete = previousItem->getNext();
            previousItem->setNext(itemToDelete->getNext());
            if (itemToDelete == last_) {
                last_ = previousItem;
            }
            else {
                itemToDelete->getNext()->setPrevious(previousItem);
            }
        }
        else {
            itemToDelete = first_;
            first_ = first_->getNext();
            if (itemToDelete == last_) {
                last_ = nullptr;
                first_ = nullptr;
            }
        }

        T result = itemToDelete->accessData();
        delete itemToDelete;
        size_--;

        return result;
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        DoubleLinkedListItem<T>* currentDoubleLinkedListItemFirst = first_;
        DoubleLinkedListItem<T>* currentDoubleLinkedListItemLast = last_;

        size_t size = size_;

        if (size % 2 == 1) {
            size++;
        }

        size /= 2;

        for (size_t i = 0; i < size; i++) {
            if (currentDoubleLinkedListItemFirst->accessData() == data) {
                return i;
            }

            if (currentDoubleLinkedListItemLast->accessData() == data) {
                return (size_ - 1) - i;
            }
            currentDoubleLinkedListItemFirst = currentDoubleLinkedListItemFirst->getNext();
            currentDoubleLinkedListItemLast = currentDoubleLinkedListItemLast->getPrevious();
        }

        return -1;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        if (size_ != 0) {
            DoubleLinkedListItem<T>* itemToDelete = first_;

            while (itemToDelete != nullptr) {
                DoubleLinkedListItem<T>* nextItem = itemToDelete->getNext();
                delete itemToDelete;
                itemToDelete = nextItem;
            }

            size_ = 0;
            first_ = nullptr;
            last_ = nullptr;
        }
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        if (index == size_ - 1) {
            return last_;
        }
        else if (index == 0) {
            return first_;
        }
        else {
            DoubleLinkedListItem<T>* currentDoubleLinkedListItem = nullptr;
            if (index <= (size_ - 1) - index) {
                currentDoubleLinkedListItem = first_;

                for (size_t i = 0; i < index; i++) {
                    currentDoubleLinkedListItem = currentDoubleLinkedListItem->getNext();
                }
            }
            else {
                currentDoubleLinkedListItem = last_;
                for (size_t i = 0; i < (size_ - 1) - index; i++) {
                    currentDoubleLinkedListItem = currentDoubleLinkedListItem->getPrevious();
                }
            }

            return currentDoubleLinkedListItem;
        }
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        return new DoubleLinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        return new DoubleLinkedListIterator(nullptr);
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
    {
        delete position_;
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
    {
        position_ = dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
    {
        return position_ != dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    }


}