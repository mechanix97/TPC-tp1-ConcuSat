#ifndef _SHARED_MEMORY_H_
#define _SHARED_MEMORY_H_

#include <string>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

template <class T>
class SharedMemory{
	int shmId;
	T* data;
public:
	SharedMemory(const std::string& file, const char c, int size);
	~SharedMemory();
	void store(const T& d);
	T* load() const;
	void storeArray(const T* a, int size);
private:
	int attachedProcesses();
};


template <class T>
SharedMemory<T>::SharedMemory(const std::string& file, const char c, int size){
	key_t key = ftok(file.c_str(), c);
	if( key == -1 ){
		//throw excp
	}
	this->shmId = shmget( key, size, 0644 | IPC_CREAT);
	if(this->shmId == -1){
		//throw excp
	}
	void* ptr = shmat(this->shmId, nullptr, 0);

	if( ptr == (void*) -1){
		//throw excp
	}
	this->data = static_cast<T*> (ptr);
	*(this->data) = T(2);
	//memset(this->data, 0, size);
}

template <class T>
SharedMemory<T>::~SharedMemory(){
	shmdt( static_cast<void *> (this->data));

	int attachedProcesses = this->attachedProcesses();

	if(! attachedProcesses){
		shmctl( this->shmId, IPC_RMID, nullptr);
	}

}

template <class T>
int SharedMemory<T>::attachedProcesses(){
	shmid_ds status;
	shmctl(this->shmId, IPC_STAT, &status);
	return status.shm_nattch;
}

template <class T>
void SharedMemory<T>::store(const T& d){
	*(this->data) = d;
}

template <class T>
T* SharedMemory<T>::load() const{
	return this->data;
}

template <class T>
void SharedMemory<T>::storeArray(const T* a, int size){
	for(int i = 0; i<size; ++i){
		this->data[i] = a[i];
	}
}

#endif
