# 脚本部分
git add build_support

# 数据部分
git add data
git add query

# 代码部分
git add src
git add temp
git add temp2

git add bin
git add bitcode

# 测试评估部分
git add test
git add tmp_jit

# 其他部分
git add help
git add jitTest
git add other
git add self_git.sh
git add README.md

git commit -m "$1"

if [ "$2" == "push" ]; then
    git push
fi

# 如果运行错误，提示正确参数信息
if [ $? -ne 0 ]; then
    echo "Usage: $0 <commit message> [push]"
fi
