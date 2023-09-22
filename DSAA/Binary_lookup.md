# 二分查找
模板1：
```cpp
int binary_lookup1(int q[n]) {
    int l = 0, r = n - 1;
    while(l < r ) {
        int mid = l + r + 1 >> 1;//当符合条件时更新为l=mid时，为了避免最后两个元素出现死循环的情况，mid = (l + r + 1) / 2
        if(check(mid)) l = mid;
        else r = mid - 1;
    }

    return l;
}
```

模板2：
```cpp
int binary_lookup2(int q[n]) {
    int l = 0, r = n - 1;
    while(l < r) {
        int mid = l + r >> 1; //当符合条件更新为r = mid时，mid = (l + r) / 2
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    return l;
}
```