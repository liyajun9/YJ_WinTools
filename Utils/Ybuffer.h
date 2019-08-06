// buffer
// author:liyajun

#pragma once
#define DEFAULT_LENGTH_OF_BUFFER 128

template <typename T>
class CYbuffer{
public:
	CYbuffer(int nObjCount = DEFAULT_LENGTH_OF_BUFFER) {
		if(nObjCount <= 0) 
			nObjCount = DEFAULT_LENGTH_OF_BUFFER;

		m_nSize = nObjCount;
		m_nPos = 0;

		m_pBufStart = new T[nObjCount];
		memset(m_pBufStart, 0, m_nSize * objSize);
		m_pBufCurrent = m_pBufStart;
	}

	~CYbuffer() {
		delete []m_pBufStart;
		m_pBufStart = NULL;
	}

	int getSize() { return m_nSize; }
	int getRemain() { return m_nSize - m_nPos; }
	int getPos() { return m_nPos; }

	int getSizeInBytes() { return m_nSize * objSize; }
	int getRemainInBytes() { return (m_nSize - m_nPos) * objSize; }		
	int getPosInBytes() { return m_nPos * objSize; }

	//pointer
	T* getBufStart() { return m_pBufStart; }
	T* getBufCurrent() { return m_pBufCurrent; }		

	void empty() { 
		memset(m_pBufStart, 0, m_nSize * objSize);
		m_pBufCurrent = m_pBufStart; 
	}

	void operator++() { 
		if(m_nPos + 1 <= m_nSize){
			m_nPos ++;
			m_pBufCurrent ++;
		} 
	}

	void operator--() { 
		if(m_nPos - 1 >= 0){
			m_nPos --;
			m_pBufCurrent --;
		} 
	}

	void operator+=(int n) {
		int avail = m_nSize - m_nPos;
		int actualN(0);
		if(n >= 0){
			actualN = n > avail ? avail : n;
		}else{
			actualN = (n + m_nPos) > 0 ? n : (0 - m_nPos);
		}
		m_nPos += actualN;
		m_pBufCurrent += actualN;
	}

	void operator-=(int n) {
		int avail = m_nPos;
		int actualN(0);
		if(n >= 0){
			actualN = n > avail ? avail : n;
		}else{
			actualN = n < (avail - m_nSize) ? (avail - m_nSize) : n;
		}
		m_nPos += actualN;
		m_pBufCurrent += actualN;
	}

private:
	int m_nSize;		
	int m_nPos;		
	T* m_pBufStart;		
	T* m_pBufCurrent; 

	static const  int objSize = sizeof(T); //obj size

};