#include <iostream>
using namespace std;

void merge(int *arr, int *temp, int sizeArr, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (int t = left; t <= right; t++)
        arr[t] = temp[t];
}

void mergeSort(int *arr, int *temp, int sizeArr, int left, int right)
{
    if (left > right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, sizeArr, left, mid);
    mergeSort(arr, temp, sizeArr, mid + 1, right);
    merge(arr, temp, sizeArr, left, mid, right);
}

class CIntArray
{
private:
    int *m_Array;
    int m_Length;

public:
    CIntArray();                       // Finished
    CIntArray(const CIntArray &other); // Finished
    CIntArray(int n);                  // Finished
    ~CIntArray();                      // Finished

    void InputArray();  // Finished
    void OutputArray(); // Finished

    CIntArray Remove();
    CIntArray Remove(int k);
    CIntArray Remove(int k, int n);
    CIntArray Replace(int oldValue, int newValue); // Finished

    CIntArray AddHead(int value);
    CIntArray AddTail(int value);
    CIntArray Insert(int k, int value);

    int Max(); // Finished
    int Min(); // Finished

    CIntArray Ascending();  // Finished
    CIntArray Descending(); // Finished
    bool IsSymmetry();      // Finished

    CIntArray MoveForward();
    CIntArray MoveForward(int n);

    CIntArray MoveBehind();
    CIntArray MoveBehind(int n);

    CIntArray Invert();        // Finished
    int Appearance(int value); // Finished
};

CIntArray::CIntArray()
{
    m_Array = nullptr;
    m_Length = 0;
}

CIntArray::CIntArray(const CIntArray &other)
{
    m_Length = other.m_Length;
    m_Array = new int[m_Length];

    for (int i = 0; i < m_Length; i++)
        m_Array[i] = other.m_Array[i];
}

CIntArray::CIntArray(int n)
{
    m_Length = n;
    m_Array = new int[m_Length]{0};
}

CIntArray::~CIntArray()
{
    if (m_Array != nullptr)
    {
        delete[] m_Array;
        m_Array = nullptr;
        m_Length = 0;
    }
}

void CIntArray::InputArray()
{
    cout << "- Input length: ";
    cin >> m_Length;

    cout << "- Input array: ";
    for (int i = 0; i < m_Length; i++)
        cin >> m_Array[i];
}

void CIntArray::OutputArray()
{
    cout << "- Array: ";
    for (int i = 0; i < m_Length - 1; i++)
        cout << m_Array[i] << ", ";
    cout << m_Array[m_Length - 1] << ".\n";
}

int CIntArray::Max()
{
    if (m_Array == nullptr)
    {
        cout << "ERROR: Array is empty.\n";
        return 0;
    }

    int max = m_Array[0];
    for (int i = 1; i < m_Length; i++)
    {
        if (m_Array[i] > max)
            max = m_Array[i];
    }
    return max;
}

int CIntArray::Min()
{
    if (m_Array == nullptr)
    {
        cout << "ERROR: Array is empty.\n";
        return 0;
    }

    int min = m_Array[0];
    for (int i = 1; i < m_Length; i++)
    {
        if (m_Array[i] < min)
            min = m_Array[i];
    }
    return min;
}

bool CIntArray::IsSymmetry()
{
    if (m_Array == nullptr)
        return true;

    for (int i = 0; i < m_Length / 2; i++)
    {
        if (m_Array[i] != m_Array[m_Length - 1 - i])
            return false;
    }
    return true;
}

CIntArray CIntArray::Invert()
{
    if (m_Array == nullptr)
        return *this;

    CIntArray ans;
    ans.m_Length = m_Length;
    ans.m_Array = new int[m_Length];

    for (int i = 0; i < m_Length; i++)
        ans.m_Array[i] = m_Array[m_Length - 1 - i];

    return ans;
}

int CIntArray::Appearance(int value)
{
    if (m_Array == nullptr)
        return 0;

    int count = 0;
    for (int i = 0; i < m_Length; i++)
    {
        if (m_Array[i] == value)
            count++;
    }

    return count;
}

CIntArray CIntArray::Ascending()
{
    if (m_Array == nullptr)
        return *this;

    CIntArray ans(*this);
    int *temp = new int[m_Length];

    mergeSort(ans.m_Array, temp, m_Length, 0, m_Length - 1);

    delete[] temp;
    return ans;
}

CIntArray CIntArray::Descending()
{
    if (m_Array == nullptr)
        return *this;
    CIntArray temp = this->Ascending();
    return temp.Invert();
}

CIntArray CIntArray::Replace(int oldValue, int newValue)
{
    if (m_Array == nullptr)
        return *this;

    CIntArray ans(*this);
    for (int i = 0; i < m_Length; i++)
    {
        if (m_Array[i] == oldValue)
            ans.m_Array[i] = newValue;
    }
    return ans;
}

CIntArray CIntArray::Remove(int k)
{
    if (m_Array == nullptr)
        return *this;

    CIntArray ans;
    ans.m_Length = m_Length - 1;
    ans.m_Array = new int[ans.m_Length];
}

int main()
{
}