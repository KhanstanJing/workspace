#include <iostream>
#include <vector>
using namespace std;

struct Box {
    // 瑕疵的大小信息
    double left, right, up, down;
    // 瑕疵的标签
    int label;
};

struct Cell {
    // 该Cell的位置
    int i, j;
    // 该Cell中包含的瑕疵
    vector<Box> flaws;
};

void findflaw(const vector<Cell>& cells) {
    vector<Cell> flawCells1;
    vector<Cell> flawCells2;
    // 遍历每个Cell
    for (const Cell& cell : cells) {
        // 1. 挑选出所有直径大于0.5mm的瑕疵
        for (const Box& box : cell.flaws) {
            if (boxDiameter(box) > 0.5) {
                cout << "探测到位于Cell(" << cell.i << ", " << cell.j << ")的瑕疵(Box " << box.label << ")的直径大小大于0.5mm，存在点状不良" << endl;
            }
        }

        // 2. 挑选出所有直径大于0.25mm且小于等于0.5mm的瑕疵
        for (const Box& box : cell.flaws) {
            if (0.25 < boxDiameter(box) && boxDiameter(box) <= 0.5) {
                // b1
                cout << "探测到位于Cell(" << cell.i << ", " << cell.j << ")的瑕疵(Box " << box.label << ")的直径大小在0.25-0.5mm之间" << endl;
                // b2
                flawCells1.push_back(cell);
                if (flawCells1.size() > 4) {
                    // b2
                    cout << "直径大于0.25且小于等于0.5mm的瑕疵为" << flawCells1.size() << "个，存在点状不良" << endl;
                    // b3
                    checkDistancesAndPrint(flawCells1, cell);
                }
            }
        }

        // 3. 挑选出所有直径大于0.1mm且小于等于0.25mm的瑕疵
        int count = 0;
        for (const Box& box : cell.flaws) {
            if (0.1 < boxDiameter(box) && boxDiameter(box) <= 0.25) {
                // b1
                cout << "探测到位于Cell(" << cell.i << ", " << cell.j << ")的瑕疵(Box " << box.label << ")的直径大小在0.1-0.25mm之间" << endl;
                // b2
                flawCells2.push_back(cell);
                // b3
                count = checkDistancesAndCount(flawCells2, cell);
                if (count > 2) {
                    // b3
                    cout << "探测到位于Cell(" << cell.i << ", " << cell.j << ")直径大于0.1且小于等于0.25mm的瑕疵(Box " << box.label << ") 1cm^2内存在另外大于两个瑕疵，存在点状不良" << endl;
                }
            }
        }
    }
}

// 计算瑕疵的直径
double boxDiameter(const Box& box) {
    return max(box.right - box.left, box.down - box.up);
}

// 计算两个Cell之间的距离
double calculateDistance(const Cell& cell1, const Cell& cell2) {
    return max(abs(cell1.i - cell2.i), abs(cell1.j - cell2.j));
}

// 检查Cell之间的距离并输出信息
void checkDistancesAndPrint(const vector<Cell>& cells, const Cell& cell) {
    // 遍历每对Cell
    for (size_t i = 0; i < cells.size(); ++i) {
        double distance = calculateDistance(cells[i], cell);
        if (distance <= 3) {
            cout << "探测到位于Cell(" << cell.i << ", " << cell.j << "中直径大于0.25且小于等于0.5mm的瑕疵5mm内存在另一个Cell(" << cells[i].i << ", " << cells[i].j << ")中也有瑕疵" << endl;
        }
    }
}

// 计算Cell之间的距离并统计符合条件的个数
int checkDistancesAndCount(const vector<Cell>& cells, const Cell& cell) {
    int count = 0;
    // 遍历每对Cell
    for (size_t i = 0; i < cells.size(); ++i) {
            double distance = calculateDistance(cells[i], cell);
            if (distance <= 3) {
                count++;
            }
    }
    return count;
}

int main() {
    vector<Cell> cells;  

    findflaw(cells);

    return 0;
}


// 接受参数：
// 一个Cell的vector，其中一个Cell的大小为640pix*640pix，约为1.88mm（1mm = 340pix），每个Cell中有如下信息：
//（1）该Cell的位置，从（0，0）开始计算
//（2）该Cell中包含的瑕疵，瑕疵记为Box
// Box中的参数：
//（1）该瑕疵的大小信息，包含四个参数：left，right，up，down，其中，left-right和up-down的最大值视为Box的直径
//（2）该瑕疵的标签label

// 实现功能：
// 1 挑选出所有直径大于0.5mm的瑕疵
//    若存在，每挑出一个
//    输出“探测到位于{Cell（i，j）}的瑕疵{Box（k）}的直径大小大于0.5mm，存在点状不良”
// 2 挑选出所有直径大于0.25mm且小于等于0.5mm的瑕疵，并且：
//  a 建立一个存放元素为Cell的向量flawcells1
//  b 每挑出一个
//     b1 输出“探测到位于{Cell（i，j）}的瑕疵{Box（k）}的直径大小在0.25-0.5mm之间”
//     b2 将该瑕疵所在的Cell放入到向量flawcells1
//        判断此时向量中的元素个数：
//        若这样的瑕疵在4个以上，即容器中的元素个数大于4个
//        输出“直径大于0.25且小于等于0.5mm的瑕疵为{n}个，存在点状不良”，其中n为该类型瑕疵的个数，也就是向量中元素的个数
//     b3 计算该瑕疵与其他直径大于0.25且小于等于0.5mm的瑕疵（也即已经被放入向量中的瑕疵）的距离。
//        判断该瑕疵所在的Cell（记为（i，j））到向量中第k个Cell（记为（ik，jk））的距离：
//        若i-ik和j-jk两个数的绝对值中的最大值小于等于3
//        输出“探测到位于{Cell（i，j）}直径大于0.25且小于等于0.5mm的瑕疵{Box（l）}5mm内存在另一个直径大于0.25且小于等于0.5mm的瑕疵{Box（k）}，存在点状不良”
// 3 挑选出所有直径大于0.1mm且小于等于0.25mm的瑕疵，并且：
//  a 建立一个存放元素为Cell的向量flawcells2，设置计数器count
//  b 每挑出一个
//     b1 输出“探测到位于{Cell（i，j）}的瑕疵{Box（k）}的直径大小在0.1-0.25mm之间”
//     b2 将该瑕疵所在的Cell放入到向量flawcells2
//        计算该瑕疵与其他直径大于0.1且小于等于0.25mm的瑕疵（也即已经被放入向量中的瑕疵）的距离。
//        判断该瑕疵所在的Cell（记为（i，j））到向量中第k个Cell（记为（ik，jk））的距离：
//        若i-ik和j-jk两个数的绝对值中的最大值小于等于3
//        计数器count+1
//        若count此时大于2
//        输出“探测到位于{Cell（i，j）}直径大于0.1且小于等于0.25mm的瑕疵{Box（l）}1cm^2内存在另外大于两个直径大于0.1且小于等于0.25mm的瑕疵，存在点状不良”