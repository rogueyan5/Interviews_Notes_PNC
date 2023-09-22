图搜索算法，包括bfs、dijkstra、A*
- 广度有限搜索
广度优先搜索在所有方向上平等的搜索，不仅适用于常规路径查找，还适用于程序地图生成、流场寻路、距离图和其他类型的地图分析。

广度优先搜索的实现依赖于queue。
```cpp
struct position{
    int x, y;
};
void bfs(vector<vector<int>> &graph, position& start, position& end)
``` 