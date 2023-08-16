# WFC2D 插件

目标是制作一个 Unreal 可用的 WFC 插件，因为最近正在学习相关的算法，打算尝试一下

参考：[wfc2d](https://anseyuyin.github.io/wfc2D/demos/2DMapEditor/) 项目

TODO List

1. Tile 类，可选的瓦片类型
2. Cell 类，方格类，用于计算
3. Slate 编写界面
   1. 选中文件夹，将文件夹内所有Texture文件导入成Tile类
   2. 将所有的Tile类给用户设置
   3. 将用户设置的导出成配置表
4. WFC 算法
   
在编写的过程中发现的问题会继续往后添加

目前存在的问题

1. WFC2DHelper.cpp 文件中 43 行 SImage 的创建使用 FSlateDynamicImageBrush 会警告 GC相关

```cpp
TSharedRef<SImage> UWFC2DHelper::CreateTileImage(UTile* Tile)
{
	return SNew(SImage).
		Image(new FSlateDynamicImageBrush(Tile->GetTexture(), TileSize, FName("Tile")));
}
```

2. WFC2DHelper.cpp 文件中 37 行 UTile 的 ID 是手动指定的

```cpp
auto Tile = NewObject<UTile>();
Tile->InitTile(1, TileTexture);
```