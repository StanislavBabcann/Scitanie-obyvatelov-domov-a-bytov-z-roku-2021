#pragma once

#include "binary_search_tree.h"
#include <random>

namespace structures
{
	/// <summary> Prvok treap-u. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TreapItem : public TableItem<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		/// <param name = "priority"> Priorita. </param>
		TreapItem(K key, T data, int priority);

		/// <summary> Getter atributu priorita. </summary>
		/// <returns> Priorita. </returns>
		int getPriority();

		/// <summary> Nastavi minimalnu prioritu. </summary>
		void minimizePriority();
	private:
		/// <summary> Kluc prvku. </summary>
		int priority_;
	};

	/// <summary> Treap. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Treap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Treap, z ktoreho sa prevezmu vlastnosti. </param>
		Treap(Treap<K, T>& other);

		/// <summary> Destruktor. </summary>
		~Treap();

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

	private:
		/// <summary> Generator nahodnej priority. </summary>
		std::default_random_engine* generator_;

		/// <summary> Skontroluje, ci je haldove usporiadanie prvkov okolo vrcholu OK. </summary>
		/// <param name = "node"> Vrchol, ktoreho susedstvo sa kontroluje. </param>
		/// <returns> true, ak je haldove usporiadanie prvkov okolo vrcholu OK, false inak. </returns>
		bool isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Vytiahne prioritu z vrcholu stromu. </summary>
		/// <param name = "node"> Vrchol, ktoreho priorita ma byt zistena. </param>
		/// <returns> Priorita vrcholu. Ak je vrchol nullptr, vrati -1. </returns>
		int extractPriority(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi lavu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt pravym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane lavym synom tohto vrchola.
		/// Potencialny lavy syn tohto vrchola sa stane pravym synom otca.
		/// </remarks>
		void rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi pravu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt lavym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane pravym synom tohto vrchola.
		/// Potencialny pravy syn tohto vrchola sa stane lavym synom otca.
		/// </remarks>
		void rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority):
		TableItem<K, T>(key, data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority()
	{
		return priority_;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority()
	{
		priority_ = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() :
		BinarySearchTree<K, T>(),
		generator_(new std::default_random_engine())
	{
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(Treap<K, T>& other) :
		Treap()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap()
	{
		delete generator_;
	}

	template<typename K, typename T>
	inline Structure& Treap<K, T>::assign(Structure& other)
	{
		if (this != &other) {
			Treap<K, T>& otherTreap = dynamic_cast<Treap<K, T>&>(other);
			BinarySearchTree<K, T>::assign(other);
			generator_ = otherTreap.generator_;
		}

		return *this;
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<Treap<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void Treap<K, T>::insert(const K& key, const T& data)
	{
		srand(time(NULL));
		int priority = generator_->operator()();

		//TreapItem<K, T>* newItem = new TreapItem<K, T>(key, data, priority);

		BinarySearchTree<K, T>::BSTTreeNode* insertedNode = new BSTTreeNode(new TreapItem<K, T>(key, data, priority));

		if (BinarySearchTree<K, T>::tryToInsertNode(insertedNode)) {
			
			while (isHeapOK(insertedNode) == false) {
				if (insertedNode->isLeftSon()) {
					rotateRightOverParent(insertedNode);
				}
				else {
					rotateLeftOverParent(insertedNode);
				}

			}
			
			
		}
		else {
			delete insertedNode->accessData();
			delete insertedNode;
		}
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K& key)
	{
		bool found = false;
		BSTTreeNode* removedNode = BinarySearchTree::findBSTNode(key, found);

		if (!found) {
			throw std::logic_error("No node with such key in Treap!");
		}
		else {
			
				TreapItem<K, T>* treapItem = dynamic_cast<TreapItem<K, T>*>(removedNode->accessData());
				treapItem->minimizePriority();

				while (!isHeapOK(removedNode)) {
					if (removedNode->isLeftSon()) {
						rotateRightOverParent(removedNode);
					}
					else {
						rotateLeftOverParent(removedNode);
					}
				}

				BinarySearchTree<K, T>::extractNode(removedNode);

				BinarySearchTree<K, T>::size_--;

				return treapItem->accessData();
			


		}
	

	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node)
	{
		

		if (node == nullptr) {
			return true;
		}
		else {
			BSTTreeNode* parent = node->getParent();

			if (parent == nullptr) {
				return true;
			}

			int priorityOfParent = extractPriority(parent);
			int nodePriority = extractPriority(node);

			if (priorityOfParent < nodePriority) {
				return true;
			} else {
				return false;
			}
		}
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node == nullptr) {
			return INT_MAX;
		}
		else {
			TreapItem<K, T>* treapItem = dynamic_cast<TreapItem<K, T>*>(node->accessData());
			return treapItem->getPriority();
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		
		if (node->isRightSon()) {
			
				BSTTreeNode* leftSon = node->getLeftSon();
				node->setLeftSon(nullptr);
				BSTTreeNode* father = node->getParent();
				BSTTreeNode* praFather = father->getParent();
				father->setRightSon(nullptr);

				if (praFather != nullptr) {
					if (father->isLeftSon()) {
						praFather->setLeftSon(node);
					}
					else {
						praFather->setRightSon(node);
					}

				}

				father->setRightSon(leftSon);
				node->setLeftSon(father);
		
			
		}
		
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		
		if (node->isLeftSon()) {
			BSTTreeNode* rightSon = node->getRightSon();
			node->setRightSon(nullptr);
			BSTTreeNode* father = node->getParent();
			BSTTreeNode* praFather = father->getParent();
			father->setLeftSon(nullptr);

			if (praFather != nullptr) {
				if (father->isLeftSon()) {
					praFather->setLeftSon(node);
				}
				else {
					praFather->setRightSon(node);
				}
			}

			father->setLeftSon(rightSon);
			node->setRightSon(father);
		}
		
	}
}