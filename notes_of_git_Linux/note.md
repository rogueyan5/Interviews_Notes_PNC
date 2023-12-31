# Git
## git面试问题汇总
### 1.git merge和git rebase的区别，更倾向于使用哪一个？
git merge保留原有分支结构，可能会出现分支结构复杂的问题，而git rebase将原有分支结构变为一条。
### 2.git cherry-pick有什么作用？
作用是挑选分支进行合并
```cpp
git cherry-pick commit-id //挑选一个版本合并到当前分支
git cherrt-pick commit-idA commit-idB //挑选多个版本合并
git cherru-pick commit-idA..commit-idB//挑选连续的多个版本合并到当前分支
```

- **分支历史**：使用merge时，合并后的分支历史将保留原始分支的提交历史，同时添加一个新的合并提交。最终的分支历史看起来像是一个分支在另一个分支上合并的结果；rebase则是合并后的分支历史被重写为一条线性的提交历史，看起来所有更改都是按顺序进行的，原始分支的提交将会被重新应用到目标分支上，形成一个新的提交历史
- **合并冲突**：多个分支上的提交修改了相同的文件或相同行时，可能会发生合并冲突，此时merge会自动尝试合并并生成合并冲突报告，我们可以手动解决冲突，然后提交合并的结果；rebase则是会在每个提交应用到目标分支之前，逐个检查是否存在冲突，如果存在冲突git会提醒我们手动解决冲突，在每个提交应用之后提交，这样可以在应用每个提交之后及时解决冲突，从而减少合并冲突的数量
- **分支顺序**：使用merge时，合并后的分支历史中，每个分支的提交顺序保持不变。提交顺序反映了每个分支上的提交时间和顺序；使用rebase时，合并后的分支历史中，所应用的分支的提交将按照它们原有的时间顺序依次出现在目标分支上，意味着原分支的提交将按照提交顺序重新排列。
- **分支合并频率**：使用merge保留了原始分支的提交历史，因此在合并分支时，可以频繁的进行合并操作，每个合并都会生成一个新的合并提交；revase以线性方式重新应用提交，因此在合并分支时，我们更适合在完成较大的功能或修复较大的错误之后再进行，可以避免频繁重新应用提交和生成大量新提交。

## 创建版本库
### git init
git init用来初始化版本库，使用此命令后工作目录下会多出一个.git文件，这个文件夹是git来跟踪管理版本库的，不要去修改和删除这个文件内的内容。
### git add [filename]
添加指定文件到暂存区内
### git status
显示当前工作区状态，红色表示在工作区，绿色表示在暂存区
### git commit -m "xxx"
提交暂存区所有文件到版本区

## 差异对比
### git diff
比较暂存区和工作区
```
git diff --cached //比较版本区和暂存区
git diff master   //比较版本区和工作区
```

## 日志+版本号
### git log
显示从最近到最远的所有提交日志
### git reflog
显示每次提交的commit id

## 版本回退+版本穿梭+版本撤销
### git reset --hard HEAD^ 
版本回退一次提交
### git reset --hard [版本号]
回退到指定版本号的版本
### git reset HAED
用版本库中的文件区替换暂存区的全部文件
### git checkout -- x.txt
用暂存区指定文件区替换工作区的指定文件
### git checkout HEAD x.txt
用版本库中的文件替换暂存区和工作区的文件
### git rm --cached x.txt
从暂存区删除文件

