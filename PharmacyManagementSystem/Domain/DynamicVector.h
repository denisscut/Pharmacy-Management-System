//#pragma once
//#include <stdio.h>
//
//template<typename T>
//class IteratorVector;
//
//template<typename T>
//class DynamicVector {
//private:
//	T* array;
//	unsigned int size;
//	unsigned int capacity;
//
//	static const unsigned int DEFAULT_CAPACITY = 4;
//
//	void resize(double factor = 2.0);
//public:
//	// constructors and destructor
//	DynamicVector() noexcept;
//	DynamicVector(unsigned int initialCapacity);
//	DynamicVector(const DynamicVector& v);
//	~DynamicVector();
//
//	// Returns a pointer to an array containing all the elements of the dynamic vector
//	T* getAll();
//	// Overloading the [] operator
//	T& operator [] (unsigned int pos);
//	// Overloading the + operator
//	DynamicVector<T>& operator+(const T& classObj);
//	// Deletes an element from a given position
//	void deleteElem(unsigned int pos);
//	// Adds an element to the end of the dynamic vector
//	void add(const T& item);
//
//	DynamicVector& operator=(const DynamicVector& ot);
//
//	//get element from position in VectorDinamic
//	T& get(int poz) noexcept;
//
//	T* getAllElems() const;
//	// Returns the size of the dynamic vector
//	unsigned int getSize();
//
//	IteratorVector<T> begin();
//	IteratorVector<T> end();
//};
//
//template<typename T>
//DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& ot) {
//	//daca se face assignment v1=v1, nu are sens sa facem
//	//operatiile de mai jos, returnam direct
//	//breakpoint in test pentru a vedea ce se compara aici
//
//	if (this == &ot) {
//		return *this;
//	}
//	//fiindca in obiectul curent punem altceva prin
//	//assignment, eliberam memoria alocata anterior
//
//	delete[] this->array;
//
//	//copiem elementele din ot si setam lungime, capacitate
//	this->array = new T[ot.capacity];
//	for (unsigned int i = 0; i < ot.size; i++) {
//		array[i] = ot.array[i];  //utilizeaza operator assignment aferent tipului T
//	}
//	this->size = ot.size;
//	this->capacity = ot.capacity;
//	return *this;
//}
//
//
//template<typename T>
//DynamicVector<T>::DynamicVector() noexcept {
//	capacity = DEFAULT_CAPACITY;
//	size = 0;
//	array = new T[DEFAULT_CAPACITY];
//}
//
//template<class T>
//DynamicVector<T>::DynamicVector(unsigned int initialCapacity)
//{
//	array = new T[initialCapacity];
//	size = 0;
//	capacity = initialCapacity;
//}
//
//template<class T>
//DynamicVector<T>::~DynamicVector()
//{
//	delete[] array;
//}
//
//template <class T>
//unsigned int DynamicVector<T>::getSize() {
//	return size;
//}
//
//template<class T>
//T* DynamicVector<T>::getAll()
//{
//	return array;
//}
//
//
//template <class T>
//T& DynamicVector<T>::operator [] (unsigned int index)
//{
//	return array[index]; // return array element
//}
//
//
//template <class T>
//DynamicVector<T>::DynamicVector(const DynamicVector& v)
//{
//	this->size = v.size;
//	this->capacity = v.capacity;
//	this->array = new T[this->capacity];
//	for (unsigned int i = 0; i < this->capacity && i < this->size; i++)
//		this->array[i] = v.array[i];
//}
//
//
//template <class T>
//void DynamicVector<T>::resize(double factor) {
//	this->capacity *= static_cast<int>(factor);
//
//	T* newArray = new T[this->capacity];
//	for (unsigned int i = 0; i < this->capacity && i < this->size; i++)
//		newArray[i] = this->array[i];
//
//	delete[] this->array;
//	this->array = newArray;
//}
//
//
//template <class T>
//void DynamicVector<T>::add(const T& e)
//{
//	if (this->size == this->capacity)
//		this->resize();
//	this->array[this->size] = e;
//	this->size++;
//}
//
//
//template<typename T>
//T& DynamicVector<T>::get(int poz) noexcept {
//	//verificam daca pozitia este valida
//	return this->array[poz];
//}
//
//
//template<class T>
//T* DynamicVector<T>::getAllElems() const
//{
//	return this->array;
//}
//
//
//template <class T>
//void DynamicVector<T>::deleteElem(unsigned int pos)
//{
//	if (pos < 0 || pos >= this->size)
//		return;
//	T* els = new T[this->capacity];
//	for (unsigned int i = 0; i < pos; i++) {
//		//els[i] = this->array[i];
//		*(els + i) = *(this->array + i);
//	}
//	for (unsigned int i = pos; i < this->size; i++) {
//		//els[i] = this->array[i + 1];
//		*(els + i) = *(this->array + i + 1);
//	}
//	delete[] this->array;
//	this->array = els;
//	this->size--;
//}
//
//
//template <class T>
//DynamicVector<T>& DynamicVector<T>::operator+(const T& classObj) {
//	this->add(classObj);
//	return *this;
//}
//
//template<typename T>
//IteratorVector<T> DynamicVector<T>::begin() {
//	return IteratorVector<T>(*this);
//}
//template<typename T>
//IteratorVector<T> DynamicVector<T>::end() {
//	return IteratorVector<T>(*this, this->size);
//}
//
////template <class T>
////DynamicVector<T>& operator+(const T& classObj, DynamicVector<T>& s) {
////	s.add(classObj);
////	return s;
////}
//
//
//template<typename T>
//class IteratorVector {
//private:
//	int current = 0;
//	const DynamicVector <T>& vec;
//public:
//	IteratorVector(const DynamicVector<T>& v) noexcept;
//	IteratorVector(const DynamicVector<T>& v, int current) noexcept;
//	IteratorVector(const IteratorVector& it) noexcept;
//	bool valid() const;
//	T& element() const;
//	void next();
//	void prev();
//	T& operator*();
//	IteratorVector& operator++();
//	IteratorVector& operator--();
//	bool operator==(const IteratorVector& ot) noexcept;
//	bool operator!=(const IteratorVector& ot) noexcept;
//	IteratorVector operator-(int r);
//	IteratorVector operator+(int r);
//	friend class DynamicVector<T>;
//};
//
//
//template<typename T>
//IteratorVector<T>::IteratorVector(const DynamicVector<T>& v) noexcept :vec{ v } { };
//template<typename T>
//IteratorVector<T>::IteratorVector(const DynamicVector<T>& v, int current) noexcept :vec{ v }, current{ current }{};
//
//template<typename T>
//IteratorVector<T>::IteratorVector(const IteratorVector<T>& it) noexcept : vec{ it.vec }, current{ it.current }{};
//
//template<typename T>
//bool IteratorVector<T>::valid() const {
//	return this->current < this->vec.size;
//}
//
//template<typename T>
//T& IteratorVector<T>::element() const {
//	return this->vec.getAllElems()[this->current];
//}
//
//template<typename T>
//void IteratorVector<T>::next() {
//	this->current++;
//}
//
//template<typename T>
//void IteratorVector<T>::prev() {
//	this->current--;
//}
//
//template<typename T>
//T& IteratorVector<T>::operator*() {
//	return this->element();
//}
//
//template<typename T>
//IteratorVector<T>& IteratorVector<T>::operator++() {
//	this->next();
//	return *this;
//}
//
//template<typename T>
//IteratorVector<T>& IteratorVector<T>::operator--() {
//	this->prev();
//	return *this;
//}
//
//template<typename T>
//IteratorVector<T> IteratorVector<T>::operator-(int r) {
//	IteratorVector<T> itCopy(*this);
//	while (r--) {
//		--(itCopy);
//	}
//	return itCopy;
//}
//
//template<typename T>
//IteratorVector<T> IteratorVector<T>::operator+(int r) {
//	IteratorVector<T> itCopy(*this);
//	while (r--) {
//		++(itCopy);
//	}
//	return itCopy;
//}
//
//
//template<typename T>
//bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept {
//	return this->current == ot.current;
//}
//template<typename T>
//bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept {
//	return !(*this == ot);
//}