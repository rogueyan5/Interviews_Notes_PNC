# 快速排序
主要思想是分治
## 单轴快排
模板：
```cpp
void quick_sort(int q[], int leftbound, int rightbound) {
    if(leftbound >= rightbound) return;
    int pivot = q[rightbound], l = leftbound, r = rightbound - 1;

    while(l <= r) {
        while(l<=r && q[l]<=pivot) ++l;
        while(l<=r && q[r]>pivot) --r;

        if(l < r) swap(q[l], q[r]);
    }
    swap(q[l], q[rightbound]);

    quick_sort(q, leftbound, l-1);
    quick_sort(q, l+1, rightbound);
}
```


# 归并排序
- 确定分界点
- 递归排序左右两部分
- 归并，将左右两个有序数组合二为一

```cpp
void merge_sort(int q[], int leftbound, int rightbound) {
    if(leftbound >= rightbound) return;
    int mid = leftbound + rightbound >> 1;
    
    merge_sort(q, leftbound, mid), merge_sort(q, mid + 1, rightbound);
    
    int k = 0, i = leftbound, j = mid + 1;
    while(i <= mid && j <= rightbound) {
        if(q[i] <= q[j]) temp[k++] = q[i++];
        else temp[k++] = q[j++];
    }
    
    while(i <= mid) temp[k++] = q[i++];
    while(j <= rightbound) temp[k++] = q[j++];
    
    for(int i=leftbound, j=0; i<=rightbound; ++i, ++j) q[i] = temp[j];
}
```