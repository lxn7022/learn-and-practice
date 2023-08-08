
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;


//链接：https://leetcode.cn/problems/1fGaJU/solutions/941911/jian-dan-yi-dong-javac-pythonjs-san-shu-nu6el/
//给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a ，b ，c ，
//使得 a + b + c = 0 ？请找出所有和为 target 且 不重复 的三元组。

// displayCombs 输出组合结果
void displayCombs(vector<vector<int>> &combs)
{
       for (auto &vec:combs){
        cout << "[";
        for (auto &it : vec)
            cout << it <<",";
        cout << "]" << endl;
    } 

}


vector<vector<int>> threeSum(vector<int>& nums, int target) {
        if (nums.size() < 3) return {};
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // 在 i + 1 ... nums.length - 1 中查找相加等于 -nums[i] 的两个数
            int _target = target - nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum == _target) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    /*
                        下面的代码相当于：
                        while (left < right) {
                            // 不管前后相不相等，left 都要往前走
                            left++;
                            if (nums[left - 1] != nums[left]) break;
                        }
                        while (left < right) {
                            // 不管前后相不相等，right 都要往后走
                            right--;
                            if (nums[right + 1] != nums[right]) break;
                        }
                     */
                    // 去重
                    while (left < right && nums[left] == nums[++left]);
                    while (left < right && nums[right] == nums[--right]);
                } else if (sum < _target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
void test_threeSum()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    vector<int> candidats = {-1,0,1,2,-1,-4};
    int target = 0;
    auto result = threeSum(candidats, target);
    displayCombs(result);
}



//原文链接：https://blog.csdn.net/ffj0721/article/details/84256818ff
//
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
    test_threeSum();
    test_kSum();
    return 0;
}

