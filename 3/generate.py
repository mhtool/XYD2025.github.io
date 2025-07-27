import matplotlib.pyplot as plt
import numpy as np
import random

# ---------- 参数 ----------
WIDTH, HEIGHT = 10, 10
WALL_PROB = 0.2  # 墙的概率
START = (0, 0)
GOAL = (HEIGHT - 1, WIDTH - 1)


# ---------- 生成迷宫 ----------
def generate_maze(width, height, wall_prob=0.2):
    maze = np.zeros((height, width), dtype=int)
    for i in range(height):
        for j in range(width):
            if random.random() < wall_prob:
                maze[i, j] = 1  # 墙
    maze[START] = 0
    maze[GOAL] = 0
    return maze


# ---------- 曼哈顿距离 ----------
def manhattan_distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


def generate_heuristic_grid(maze, goal):
    h, w = maze.shape
    grid = np.full_like(maze, -1)  # 默认全是墙
    for i in range(h):
        for j in range(w):
            if maze[i, j] == 0:
                grid[i, j] = manhattan_distance(i, j, *goal)
    return grid


# ---------- 绘图函数 ----------
def draw_grid_background(ax, maze):
    cmap = plt.cm.get_cmap('gray_r')
    ax.imshow(maze, cmap=cmap, extent=(0, maze.shape[1], maze.shape[0], 0))
    ax.set_xticks(np.arange(maze.shape[1] + 1))
    ax.set_yticks(np.arange(maze.shape[0] + 1))
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(color='black', linewidth=0.5)
    ax.set_aspect('equal')


def plot_maze(maze, save_path=None):
    fig, ax = plt.subplots(figsize=(6, 6))
    draw_grid_background(ax, maze)
    ax.text(START[1] + 0.5, START[0] + 0.5, 'S', color='green', ha='center', va='center', fontsize=12, weight='bold')
    ax.text(GOAL[1] + 0.5, GOAL[0] + 0.5, 'G', color='red', ha='center', va='center', fontsize=12, weight='bold')
    ax.set_title("Maze")
    plt.tight_layout()
    
    # 保存图像
    if save_path:
        plt.savefig(save_path, dpi=300, bbox_inches='tight')
        print(f"迷宫图像已保存到: {save_path}")
    
    plt.show()


def plot_heuristics_on_maze(maze, heuristic_grid, save_path=None):
    fig, ax = plt.subplots(figsize=(6, 6))
    
    # 创建热力图背景
    # 为热力图创建一个数组，墙为 NaN，其他位置为启发式值
    heatmap_data = np.full_like(maze, np.nan, dtype=float)
    
    # 获取有效的启发式值范围
    valid_heuristics = []
    for i in range(maze.shape[0]):
        for j in range(maze.shape[1]):
            if maze[i, j] == 0:  # 非墙位置
                heatmap_data[i, j] = heuristic_grid[i, j]
                valid_heuristics.append(heuristic_grid[i, j])
    
    # 使用热力图显示启发式值
    if valid_heuristics:
        vmin = min(valid_heuristics)
        vmax = max(valid_heuristics)
        
        # 使用 viridis 颜色映射（从深紫色到黄色）
        cmap = plt.cm.get_cmap('viridis_r')  # 反转颜色映射，使距离近的颜色更暖
        im = ax.imshow(heatmap_data, cmap=cmap, vmin=vmin, vmax=vmax, 
                       extent=(0, maze.shape[1], maze.shape[0], 0))
        
        # 添加颜色条
        cbar = plt.colorbar(im, ax=ax, shrink=0.8)
        cbar.set_label('曼哈顿距离', rotation=270, labelpad=15)
    
    # 绘制墙壁（黑色）
    for i in range(maze.shape[0]):
        for j in range(maze.shape[1]):
            if maze[i, j] == 1:  # 墙
                ax.add_patch(plt.Rectangle((j, i), 1, 1, facecolor='black', edgecolor='black'))
    
    # 添加网格
    ax.set_xticks(np.arange(maze.shape[1] + 1))
    ax.set_yticks(np.arange(maze.shape[0] + 1))
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(color='white', linewidth=0.5, alpha=0.7)
    ax.set_aspect('equal')
    
    # 添加数值标签
    for i in range(maze.shape[0]):
        for j in range(maze.shape[1]):
            if maze[i, j] == 0:
                value = heuristic_grid[i, j]
                # 根据背景色调整文字颜色
                text_color = 'white' if value > vmax * 0.6 else 'black'
                ax.text(j + 0.5, i + 0.5, str(value), ha='center', va='center', 
                       color=text_color, fontsize=10, weight='bold')

    # 添加起点和终点标记
    ax.text(START[1] + 0.5, START[0] + 0.5, 'S', color='red', ha='center', va='center', 
           fontsize=14, weight='bold', bbox=dict(boxstyle="circle,pad=0.1", facecolor='white', alpha=0.8))
    ax.text(GOAL[1] + 0.5, GOAL[0] + 0.5, 'G', color='red', ha='center', va='center', 
           fontsize=14, weight='bold', bbox=dict(boxstyle="circle,pad=0.1", facecolor='white', alpha=0.8))
    
    ax.set_title("Manhattan Distance Heuristic (A*) - 热力图")
    plt.tight_layout()
    
    # 保存图像
    if save_path:
        plt.savefig(save_path, dpi=300, bbox_inches='tight')
        print(f"启发式热力图已保存到: {save_path}")
    
    plt.show()


# ---------- 主流程 ----------
if __name__ == "__main__":
    maze = generate_maze(WIDTH, HEIGHT, WALL_PROB)
    heuristic_grid = generate_heuristic_grid(maze, GOAL)

    # 保存图像到文件
    plot_maze(maze, save_path="maze.png")
    plot_heuristics_on_maze(maze, heuristic_grid, save_path="heuristic_heatmap.png")
