
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;


//原文链接：https://blog.csdn.net/ffj0721/article/details/84256818ff
//LeetCode 之 n 个数之和（Sum n）
/**
 * 
 * @param nums
 *            排序后目标数组
 * @param target
 *            累加目标数值
 * @param k
 *            个数
 * @param index
 *            起始下标
 * @return
 */

int len = 0;  //len是全局变量
vector<vector<int> > kSum(vector<int> &nums, int target, int k, int index)
{

    vector<vector<int> > res;
    len = nums.size();

    if (index >= len)
        return res;
    if (k == 2) { // 两数取和
        int i = index, j = len - 1;
        while (i < j) {
            // 满足条件塞入集合
            if (target - nums[i] == nums[j]) {
                vector<int> temp;
                temp.push_back(nums[i]);
                temp.push_back(nums[j]);
                res.push_back(temp);
                while (i < j && nums[i] == nums[i + 1]) // 跳过重复数值
                    i++;
                while (i < j && nums[j] == nums[j - 1]) // 跳过重复数值
                    j--;
                i++;
                j--;
            } else if (target - nums[i] > nums[j])
                i++;
            else
                j--;
        }
    } else {
        for (int i = index; i < len - k + 1; i++) {
            // 调用递归 DFS
            vector<vector<int> > temp = kSum(nums, target - nums[i], k - 1, i + 1);
            // 若是有值返回则将该数塞入，无则不进行任何操作
            if (temp.size() > 0) {
                for (auto &it : temp) {
                    
                    it.push_back(nums[i]); // 将满足条件数值塞入
                }
                res.insert(res.end(), temp.begin(), temp.end());
            }
            while (i < len - 1 && nums[i] == nums[i + 1]) // 跳过重复数值
                i++;
        }
    }
    return res;
}

vector<vector<int> > combinationSum(vector<int> &nums, int target)
{
    vector<vector<int>> combs;
    sort(nums.begin(), nums.end());
    for (int k = 2; k <= nums.size(); k++)
    {
        vector<vector<int> > temp =  kSum(nums, target, k, 0);
        combs.insert(combs.end(), temp.begin(), temp.end());
    }
    return combs;
}

void displayCombs(vector<vector<int>> &combs)
{
       for (auto &vec:combs){
        cout << "[";
        for (auto &it : vec)
            cout << it <<",";
        cout << "]" << endl;
    } 

}

void test_kSum()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    vector<int> candidats = {1, 0, -1, 0, -2, 2};
    int target = 0;
    auto result = combinationSum(candidats, target);
    displayCombs(result);
}

int main()
{
    test_kSum();
    return 0;
}

