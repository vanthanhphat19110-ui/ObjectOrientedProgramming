#include <iostream>
#include <stdlib.h>
#include <ctime>
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
    if (left >= right)
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
    CIntArray();
    CIntArray(const CIntArray &other);
    CIntArray &operator=(const CIntArray &other);
    CIntArray(int n);
    ~CIntArray();

    void InputArray();
    void OutputArray();

    CIntArray Remove();
    CIntArray Remove(int k);
    CIntArray Remove(int k, int n);
    CIntArray Replace(int oldValue, int newValue);

    CIntArray AddHead(int value);
    CIntArray AddTail(int value);
    CIntArray Insert(int k, int value);

    int Max();
    int Min();

    CIntArray Ascending();
    CIntArray Descending();
    bool IsSymmetry();

    CIntArray MoveForward();
    CIntArray MoveForward(int n);

    CIntArray MoveBehind();
    CIntArray MoveBehind(int n);

    CIntArray Invert();
    int Appearance(int value);
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

CIntArray &CIntArray::operator=(const CIntArray &other)
{
    if (this == &other)
        return *this;

    if (m_Array != nullptr)
    {
        delete[] m_Array;
        m_Array = nullptr;
        m_Length = 0;
    }

    m_Length = other.m_Length;
    m_Array = new int[m_Length];

    for (int i = 0; i < m_Length; i++)
        m_Array[i] = other.m_Array[i];

    return *this;
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
    if (m_Array != nullptr)
    {
        delete[] m_Array;
        m_Array = nullptr;
        m_Length = 0;
    }

    cout << "- Input length: ";
    cin >> m_Length;
    m_Array = new int[m_Length];

    for (int i = 0; i < m_Length; i++)
        m_Array[i] = rand() % (2 * 99 + 1) - 99;
}

void CIntArray::OutputArray()
{
    if (m_Array == nullptr || m_Length == 0)
    {
        cout << "- Array: empty.\n";
        return;
    }

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
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    if (newValue < -99 || newValue > 99)
    {
        cout << "ERROR: Value is not in range [-99,99].\n";
        return *this;
    }

    CIntArray ans(*this);
    for (int i = 0; i < m_Length; i++)
    {
        if (m_Array[i] == oldValue)
            ans.m_Array[i] = newValue;
    }

    return ans;
}

CIntArray CIntArray::Remove()
{
    if (m_Array == nullptr)
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    bool existed[199] = {false};
    int countUnique = 0;
    for (int i = 0; i < m_Length; i++)
    {
        int index = m_Array[i] + 99;
        if (existed[index] == false)
        {
            existed[index] = true;
            countUnique++;
        }
    }

    for (int i = 0; i < 199; i++)
        existed[i] = false;

    CIntArray ans;
    ans.m_Length = countUnique;
    ans.m_Array = new int[ans.m_Length];

    int j = 0;
    for (int i = 0; i < m_Length; i++)
    {
        int index = m_Array[i] + 99;
        if (existed[index] == false)
        {
            existed[index] = true;
            ans.m_Array[j++] = m_Array[i];
        }
    }

    return ans;
}

CIntArray CIntArray::Remove(int k)
{
    if (m_Array == nullptr)
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    if (k < 0 || k >= m_Length)
    {
        cout << "ERROR: Position is not valid.\n";
        return *this;
    }

    CIntArray ans;
    ans.m_Length = m_Length - 1;
    ans.m_Array = new int[ans.m_Length];

    int j = 0;
    for (int i = 0; i < m_Length; i++)
    {
        if (i != k)
            ans.m_Array[j++] = m_Array[i];
    }

    return ans;
}

CIntArray CIntArray::Remove(int k, int n)
{
    if (m_Array == nullptr)
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    if (k < 0 || k >= m_Length || n <= 0)
    {
        cout << "ERROR: Position is not valid.\n";
        return *this;
    }

    int countActualRemove = ((k + n) > m_Length) ? (m_Length - k) : n;
    CIntArray ans;
    ans.m_Length = m_Length - countActualRemove;
    ans.m_Array = new int[ans.m_Length];

    int j = 0;
    for (int i = 0; i < m_Length; i++)
    {
        if (i < k || i >= k + countActualRemove)
            ans.m_Array[j++] = m_Array[i];
    }

    return ans;
}

CIntArray CIntArray::AddHead(int value)
{
    if (value < -99 || value > 99)
    {
        cout << "ERROR: Value is not in range [-99,99].\n";
        return *this;
    }

    CIntArray ans;
    ans.m_Length = m_Length + 1;
    ans.m_Array = new int[ans.m_Length];
    ans.m_Array[0] = value;

    if (m_Array == nullptr)
        return ans;

    int j = 1;
    for (int i = 0; i < m_Length; i++)
        ans.m_Array[j++] = m_Array[i];

    return ans;
}

CIntArray CIntArray::AddTail(int value)
{
    if (value < -99 || value > 99)
    {
        cout << "ERROR: Value is not in range [-99,99].\n";
        return *this;
    }

    CIntArray ans;
    ans.m_Length = m_Length + 1;
    ans.m_Array = new int[ans.m_Length];

    if (m_Array == nullptr)
    {
        ans.m_Array[0] = value;
        return ans;
    }

    for (int i = 0; i < m_Length; i++)
        ans.m_Array[i] = m_Array[i];
    ans.m_Array[ans.m_Length - 1] = value;

    return ans;
}

CIntArray CIntArray::Insert(int k, int value)
{
    if (k < 0 || k > m_Length)
    {
        cout << "ERROR: Position is not valid.\n";
        return *this;
    }

    if (value < -99 || value > 99)
    {
        cout << "ERROR: Value is not in range [-99,99].\n";
        return *this;
    }

    if (k == 0)
        return this->AddHead(value);

    if (k == m_Length)
        return this->AddTail(value);

    CIntArray ans;
    ans.m_Length = m_Length + 1;
    ans.m_Array = new int[ans.m_Length];

    int j = 0;
    for (int i = 0; i < m_Length; i++)
    {
        if (j != k)
            ans.m_Array[j++] = m_Array[i];
        else
        {
            ans.m_Array[j++] = value;
            i--;
        }
    }

    return ans;
}

CIntArray CIntArray::MoveForward(int n)
{
    if (m_Array == nullptr || m_Length == 0)
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    n = n % m_Length;
    CIntArray ans;
    ans.m_Length = m_Length;
    ans.m_Array = new int[ans.m_Length];

    for (int i = 0; i < m_Length; i++)
        ans.m_Array[i] = m_Array[(i + n) % m_Length];

    return ans;
}

CIntArray CIntArray::MoveForward()
{
    return this->MoveForward(1);
}

CIntArray CIntArray::MoveBehind(int n)
{
    if (m_Array == nullptr || m_Length == 0)
    {
        cout << "ERROR: Array is empty.\n";
        return *this;
    }

    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    n = n % m_Length;
    CIntArray ans;
    ans.m_Length = m_Length;
    ans.m_Array = new int[ans.m_Length];

    for (int i = 0; i < m_Length; i++)
        ans.m_Array[(i + n) % m_Length] = m_Array[i];

    return ans;
}

CIntArray CIntArray::MoveBehind()
{
    return this->MoveBehind(1);
}

int main()
{
    srand(time(0));
    CIntArray test, temp;

    test.InputArray();
    test.OutputArray();

    cout << "- Remove(): ";
    temp = test.Remove();
    temp.OutputArray();

    int k, n;
    cout << "- Input k: ";
    cin >> k;
    cout << "- Input n: ";
    cin >> n;

    cout << "- Remove(k): ";
    temp = test.Remove(k);
    temp.OutputArray();

    cout << "- Remove(k, n): ";
    temp = test.Remove(k, n);
    temp.OutputArray();

    int oldValue, newValue;
    cout << "- Input old value: ";
    cin >> oldValue;
    cout << "- Input new value: ";
    cin >> newValue;

    cout << "- Replace(oldValue, newValue): ";
    temp = test.Replace(oldValue, newValue);
    temp.OutputArray();

    int value;
    cout << "- Input value: ";
    cin >> value;

    cout << "- AddHead(value): ";
    temp = test.AddHead(value);
    temp.OutputArray();

    cout << "- AddTail(value): ";
    temp = test.AddTail(value);
    temp.OutputArray();

    cout << "- Insert(k, value): ";
    temp = test.Insert(k, value);
    temp.OutputArray();

    cout << "- Max(): " << test.Max() << ".\n";
    cout << "- Min(): " << test.Min() << ".\n";

    cout << "- Ascending(): ";
    temp = test.Ascending();
    temp.OutputArray();

    cout << "- Descending(): ";
    temp = test.Descending();
    temp.OutputArray();

    if (test.IsSymmetry())
        cout << "- IsSymmetry(): True.\n";
    else
        cout << "- IsSymmetry(): False.\n";

    cout << "- MoveForward(): ";
    temp = test.MoveForward();
    temp.OutputArray();

    cout << "- MoveForward(n): ";
    temp = test.MoveForward(n);
    temp.OutputArray();

    cout << "- MoveBehind(): ";
    temp = test.MoveBehind();
    temp.OutputArray();

    cout << "- MoveBehind(n): ";
    temp = test.MoveBehind(n);
    temp.OutputArray();

    return 0;
}