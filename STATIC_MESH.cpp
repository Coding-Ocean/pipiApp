#include "../pipiLib/pch.h"
#include "../pipiLib/GRAPHIC.h"
#include "STATIC_MESH.h"

STATIC_MESH::STATIC_MESH()
{
	create();
}

STATIC_MESH::~STATIC_MESH()
{
	ConstBuf1->Unmap(0, nullptr);
	ConstBuf2->Unmap(0, nullptr);
}

void STATIC_MESH::create()
{
	auto& g = GRAPHIC::instance();
	//頂点バッファをつくる
	{
		//生データ
		float vertices[] = {
			//position           normal             texcoord
			-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,//左上
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,//左下
			 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,//右上
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,//右下
		};
		g.createVertexBuf(vertices, sizeof(vertices), 4*8, &VertexBuf, &Vbv);
	}
	//頂点インデックスバッファをつくる
	{
		unsigned short indices[] = {
			0,1,2,
			3,2,1,
		};
		g.createIndexBuf(indices, sizeof(indices), &IndexBuf, &Ibv);

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
		LPCWSTR filename = L"assets/penguin2.png";
		g.createTextureBuf(filename, &TextureBuf);
	}
	//ディスクリプタヒープをつくる
	{
		g.createCbvTbvHeap(ConstBuf1.Get(), ConstBuf2.Get(), TextureBuf.Get(), &CbvTbvHeap);
	}
}

void STATIC_MESH::update(const MATRIX& world)
{
	ConstBuf1Map->world = world;
}

void STATIC_MESH::draw()
{
	auto& g = GRAPHIC::instance();
	g.draw(Vbv,Ibv,CbvTbvHeap.Get());
}
