#include "../pipiLib/pch.h"
#include "../pipiLib/GRAPHIC.h"
#include "SQUARE.h"

SQUARE::SQUARE(LPCWSTR filename)
{
	create(filename);
}

SQUARE::~SQUARE()
{
	ConstBuf1->Unmap(0, nullptr);
	ConstBuf2->Unmap(0, nullptr);
}

void SQUARE::create(LPCWSTR filename)
{
	auto& g = GRAPHIC::instance();
	//頂点バッファ、位置をつくる
	{
		//位置の生データ
		float positions[] = {
			-0.5f,  0.5f, 0.0f,//左上
			-0.5f, -0.5f, 0.0f,//左下
			 0.5f,  0.5f, 0.0f,//右上
			 0.5f, -0.5f, 0.0f,//右下
		};
		g.createVertexBuf(positions, sizeof(positions), 4*3, &PositionBuf, &PositionBufView);
	}
	//頂点バッファ、法線ベクトルをつくる
	{
		//法線の生データ
		float normals[] = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
		};
		g.createVertexBuf(normals, sizeof(normals), 4*3, &NormalBuf, &NormalBufView);
	}
	//頂点バッファ、テクスチャ座標をつくる
	{
		//テクスチャ座標の生データ
		float texcoords[] = {
			0.0f, 0.0f,//左上
			0.0f, 1.0f,//左下
			1.0f, 0.0f,//右上
			1.0f, 1.0f,//右下
		};
		g.createVertexBuf(texcoords, sizeof(texcoords), 4*2, &TexcoordBuf, &TexcoordBufView);
	}
	//頂点インデックスバッファをつくる
	{
		unsigned short indices[] = {
			0,1,2,
			3,2,1,
		};
		g.createIndexBuf(indices, sizeof(indices), &IndexBuf, &IndexBufView);

	}
	//コンスタントバッファ１をつくる
	{
		g.createConstBuf(sizeof(GRAPHIC::CONST_BUF1), &ConstBuf1, (void**)&ConstBuf1Map);
	}
	//コンスタントバッファ２をつくる
	{
		g.createConstBuf(sizeof(GRAPHIC::CONST_BUF2), &ConstBuf2, (void**)&ConstBuf2Map);
		ConstBuf2Map->diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		ConstBuf2Map->ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	}
	//テクスチャバッファをつくる
	{
		g.createTextureBuf(filename, &TextureBuf);
	}
	//ディスクリプタヒープをつくる
	{
		g.createCbvTbvHeap(ConstBuf1.Get(), ConstBuf2.Get(), TextureBuf.Get(), &CbvTbvHeap);
	}
}

void SQUARE::update(const MATRIX& world)
{
	ConstBuf1Map->world = world;
}

void SQUARE::draw()
{
	auto& g = GRAPHIC::instance();
	g.draw(
		PositionBufView,
		NormalBufView,
		TexcoordBufView,
		IndexBufView,
		CbvTbvHeap.Get()
	);
}
