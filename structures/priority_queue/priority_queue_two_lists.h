#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include "priority_queue_linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();
		PriorityQueueTwoLists(int paRatioOfShortList);

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		void restructuring();

		int ratioOfShortList_;

	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
		ratioOfShortList_ = -1;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(int paRatioOfShortList) :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
		ratioOfShortList_ = paRatioOfShortList;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete shortList_;
		delete longList_;
		shortList_ = nullptr;
		longList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		PriorityQueueTwoLists<T>& newTwoLists = dynamic_cast<PriorityQueueTwoLists<T>&>(other);
		shortList_->clear();
		shortList_->assign(*newTwoLists.shortList_);
		longList_->assign(*newTwoLists.longList_);

		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();
		
		while (longList_->size() != 0) {
			PriorityQueueItem<T>* removedItem = longList_->removeAt(0);
			delete removedItem;
		}
		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if (longList_->size() == 0) {
			PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(priority, data);
			if (removedItem != nullptr) {
				longList_->add(removedItem);
			}
		}
		else {
			if (shortList_->size() == 0) {
				restructuring();
				this->push(priority, data);
			}
			else {
				if (priority < shortList_->minPriority()) {
					PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(priority, data);
					if (removedItem != nullptr) {
						longList_->add(removedItem);
					}
				}
				else {
					PriorityQueueItem<T>* itemForLongList = new PriorityQueueItem<T>(priority, data);
					longList_->add(itemForLongList);
				}
			}
		}

		
		
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		if (shortList_->size() == 0) {
			if (longList_->size() == 0) {
				throw std::logic_error("PriorityQueueTwoLists is empty!");
			}
			else {
				restructuring();
			}
		}
		return shortList_->pop();
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		if (shortList_->size() == 0 && longList_->size() != 0) {
			restructuring();
		}
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		if (shortList_->size() == 0 && longList_->size() != 0) {
			restructuring();
		}
		return shortList_->peekPriority();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::restructuring()
	{
		int newSizeOfShort;
		if (ratioOfShortList_ == -1) {
			newSizeOfShort = sqrt(longList_->size());
		}
		else if (ratioOfShortList_ == 1000) {
			newSizeOfShort = longList_->size() / ratioOfShortList_;
			ratioOfShortList_ = newSizeOfShort;
		}
		else if (ratioOfShortList_ == 2) {
			newSizeOfShort = longList_->size() / 2;
		}
		else {
			newSizeOfShort = ratioOfShortList_;
		}

		if (newSizeOfShort < 4) {
			newSizeOfShort = 4;
		}
		shortList_->trySetCapacity(newSizeOfShort);

		LinkedList<PriorityQueueItem<T>*>* helpList = new LinkedList<PriorityQueueItem<T>*>;

		while (longList_->size() != 0) {
			PriorityQueueItem<T>* itemFromLongList = longList_->removeAt(0);

			PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(itemFromLongList->getPriority(), itemFromLongList->accessData());
			delete itemFromLongList;
			if (removedItem != nullptr) {
				helpList->add(removedItem);
			}
		}
		longList_->clear();
		longList_->assign(*helpList);

		delete helpList;
	}
}