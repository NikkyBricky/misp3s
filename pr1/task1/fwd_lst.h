#pragma once
#include <memory>
#include <utility>
#include <stdexcept>

template <typename T>
struct Node{
		std::unique_ptr<Node> next;
		T value;
		Node(T val) : value(std::move(val)) {} 
};

template <typename T>
class ForwardList{
	private:
		std::unique_ptr<Node<T>> _head;
	public:
		ForwardList() = default;

		ForwardList(const ForwardList& other) {
			if (!other._head){
				return;
			}
			
			_head = std::make_unique<Node<T>>(other._head->value);

			Node<T>* ptr1 = other._head.get();
			Node<T>* ptr2 = _head.get();

			while (ptr1->next){
				ptr1 = (ptr1->next).get();
				auto n = std::make_unique<Node<T>>(ptr1->value);
				ptr2->next = std::move(n);
				ptr2 = (ptr2->next).get();
			}
		}

		ForwardList& operator=(ForwardList other) noexcept{
			std::swap(_head, other._head);
			return *this;
		}

		ForwardList(ForwardList&& other) noexcept : _head(std::move(other._head)) {}
		

		~ForwardList(){
			while (_head){
				_head = std::move(_head->next);
			}
		}

		void pushFront(const T& v){
			auto n = std::make_unique<Node<T>>(v);
			n->next = std::move(_head);
			_head = std::move(n);
		}

		void popFront(){
			if (!_head){
				return;
			}

			_head = std::move(_head->next);
		}

		bool empty() const{
			return _head == nullptr;
		}

		const T& front() const{
			if (!_head){
				throw std::out_of_range("No elements in the list");
			}
			return _head->value;
		}
};
