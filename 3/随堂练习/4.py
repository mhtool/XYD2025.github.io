n = int(input())
a, b = map(int, input().split())
arr = [tuple(map(int, input().split())) for _ in range(n)]
ans = 0
arr.sort(key=lambda x: x[0] * x[1])
for i in range(n):
    if a // arr[i][1] > ans:
        ans = a // arr[i][1]
    a *= arr[i][0]
print(ans)
