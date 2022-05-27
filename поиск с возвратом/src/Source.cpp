
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>



class square
{
public:
    int x_;
    int y_;
    int size_;

    square(int x, int y, int size) : x_(x), y_(y), size_(size)
    {

    }
    void print()
    {

        std::cout << x_ + 1 << " " << y_ + 1 << " " << size_ << std::endl;
        //std::cout << std::endl;
    }
};

square operator * (square s, int a)
{
    return square(s.x_ * a, s.y_ * a, s.size_ * a);
}

void fill_arr(int** arr, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            arr[i][j] = 0;
    }
}
void fill_arr(int** arr, int size_x, int size_y)
{
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++)
            arr[i][j] = 0;
    }
}

void print_arr(int** arr, int size)
{
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            std::cout << std::setw(3) << std::setprecision(1) << arr[i][j];
        std::cout << std::endl;
    }
}
void print_arr(int** arr, int size_x, int size_y)
{
    std::cout << std::endl;
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++)
            std::cout << std::setw(3) << std::setprecision(1) << arr[i][j];
        std::cout << std::endl;
    }
}




void fill_square(int** arr, int a, int b, int size, int c)
{
    for (int i = a; i < a + size; i++)
        for (int j = b; j < b + size; j++)
            arr[i][j] = c;
}
void fill_square(int** arr, square s, int c)
{
    for (int i = s.x_; i < s.x_ + s.size_; i++)
        for (int j = s.y_; j < s.y_ + s.size_; j++)
            arr[i][j] = c;
}

void find_max_square(int** arr, std::vector<square>& current, int a, int b, int field_size)
{
    bool is_size = true;
    int step = 0;
    while (is_size && step < field_size)
    {
        for (int i = a; i < a + step; i++)
            if (b + step >= field_size || i >= field_size || arr[i][b + step] != 0)
                is_size = false;
        for (int i = b; i < b + step; i++)
            if (a + step >= field_size || i >= field_size || arr[a + step][i] != 0)
                is_size = false;
        step++;

        //std::cout << step << std::endl;
    }
    current.push_back(square(a, b, step - 1));

    fill_square(arr, a, b, step - 1, current.size());

}
void find_max_square(int** arr, std::vector<square>& current, int a, int b, int field_size_x, int field_size_y)
{
    bool is_size = true;
    int step = 0;
    while (is_size)
    {
        if (step >= std::min(field_size_x, field_size_y) - 1)
            is_size = false;
        for (int i = a; i < a + step; i++)
            if (b + step >= field_size_y || i >= field_size_x || arr[i][b + step] != 0)
                is_size = false;
        for (int i = b; i < b + step; i++)
            if (a + step >= field_size_x || i >= field_size_y || arr[a + step][i] != 0)
                is_size = false;
        step++;

        //std::cout << step << std::endl;
    }
    current.push_back(square(a, b, step - 1));

    fill_square(arr, a, b, step - 1, current.size());

}

void erase_squre(int** arr, square s)
{

    for (int i = s.x_; i < s.x_ + s.size_; i++)
        for (int j = s.y_; j < s.y_ + s.size_; j++)
            arr[i][j] = 0;
}


void fill(int** arr, std::vector<square>& current, int field_size)
{
    for (int i = 0; i < field_size; i++)
        for (int j = 0; j < field_size; j++)
            if (arr[i][j] == 0)
                find_max_square(arr, current, i, j, field_size);
}

void fill(int** arr, std::vector<square>& current, int field_size_x, int field_size_y)
{
    for (int i = 0; i < field_size_x; i++)
        for (int j = 0; j < field_size_y; j++)
            if (arr[i][j] == 0)
                find_max_square(arr, current, i, j, field_size_x, field_size_y);
}

void fill_1(int** arr, std::vector<square>& current, int field_size, int min_size)
{
    for (int i = 0; i < field_size; i++)
        for (int j = 0; j < field_size; j++)
            if (arr[i][j] == 0)
            {
                find_max_square(arr, current, i, j, field_size);
                if (current.size() >= min_size)
                    return;
            }
}

void fill_1(int** arr, std::vector<square>& current, int field_size_x, int field_size_y, int min_size)
{
    for (int i = 0; i < field_size_x; i++)
        for (int j = 0; j < field_size_y; j++)
            if (arr[i][j] == 0)
            {
                find_max_square(arr, current, i, j, field_size_x, field_size_y);
                if (current.size() >= min_size)
                    return;
            }
}



void print_squares(std::vector<square>& current, int scale = 1)
{
    for (auto i : current)
        (i * scale).print();
}

int min_del(int a)
{
    for (int i = 2; i <= sqrt(a) + 1; i++)
    {
        if (a % i == 0)
            return i;
    }
    return 1;
}
int max_del(int a)
{
    for (int i = sqrt(a); i > 1; i--)
    {
        if (a % i == 0)
            return i;
    }
    return 1;
}


unsigned int greatest_common_divisor(unsigned int a, unsigned int b) {
    if (a == b)
        return max_del(a);
    if (a > b)
        return greatest_common_divisor(a - b, b);
    return greatest_common_divisor(a, b - a);
}

void init_start_cover(std::vector<square>& current, int** arr, int size)
{
    if (size == 2)
    {
        square s1(0, 0, 1);
        square s2(0, 1, 1);
        square s3(1, 0, 1);
        square s4(1, 1, 1);

        current.push_back(s1);
        current.push_back(s2);
        current.push_back(s3);
        current.push_back(s4);
    }
    else {
        square s1(0, 0, ceil((float)size / 2));
        square s2(0, ceil((float)size / 2), ceil((float)size / 2) - 1);
        square s3(ceil((float)size / 2), 0, ceil((float)size / 2) - 1);

        current.push_back(s1);
        current.push_back(s2);
        current.push_back(s3);
    }

    // #fil matrix with start squares
    for (int i = 0; i < current.size(); i++)
    {
        fill_square(arr, current[i], i + 1);
    }
    // #fil matrix
    fill(arr, current, size);
}

void go_(int size_x, int size_y)
{
    int** res_arr = new int* [size_x];
    for (int i = 0; i < size_x; i++)
        res_arr[i] = new int[size_y];
    fill_arr(res_arr, size_x, size_y);

    //print_arr(res_arr, size_x, size_y);
    std::vector<square> result;
    std::vector<square> current;

    int scale = greatest_common_divisor(size_x, size_y);

    size_x = size_x / scale;
    size_y = size_y / scale;


    int** arr = new int* [size_x];
    for (int i = 0; i < size_x; i++)
        arr[i] = new int[size_y];
    fill_arr(arr, size_x, size_y);


    if (size_x == size_y)
        init_start_cover(current, arr, size_x);


    fill(arr, current, size_x, size_y);
    result = current;
    int min_size = current.size();

    print_arr(arr, size_x, size_y);
    int last = min_size - 1;
    while (current[0].size_ >= std::min(size_x, size_y) / 2)
    {

        last = 0;
        for (int i = current.size() - 1; i >= 0; i--)
            if (current[i].size_ > 1)
            {
                last = i;
                break;
            }

        if ((size_x == size_y) && (last <= 2)) break;

        if (last + 1 > min_size)
        {
            for (int i = current.size() - 1; i >= last; i--)
            {
                erase_squre(arr, current[i]);
                current.erase(current.end() - 1);
            }
            continue;
        }



        for (int i = current.size() - 1; i >= last; i--)
        {
            erase_squre(arr, current[i]);
            if (i != last)
                current.erase(current.end() - 1);
        }

        current[last].size_--;
        fill_square(arr, current[last].x_, current[last].y_, current[last].size_, last + 1);

        fill_1(arr, current, size_x, size_y, min_size);
        if (current.size() < min_size)
        {
            min_size = current.size();
            result = current;
        }
    }

    std::cout << min_size << std::endl;
    for (int i = 0; i < result.size(); i++)
    {
        fill_square(res_arr, result[i] * scale, i + 1);
    }
    print_arr(res_arr, size_x * scale, size_y * scale);

    //print_squares(result, scale);
}

int main()
{
    int x, y;
    std::cin >> x;
    std::cin >> y;
    go_(x, y);


    /*for (int i = 2; i < 10; i++)
        for (int j = 2; j < 10; j++)
        {
            std::cout << "a == " << i << " b == " << j << " min_cover = ";
            go_(i, j);
        }   

    int n = 0;
    while (n != 1) {
        std::cin >> x;
        std::cin >> y;
        std::cout << "a = " << x << " b = " << y << " min_cover = ";
        go_(x, y);
    }*/
    return 0;
}
