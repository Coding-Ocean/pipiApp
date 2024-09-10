#pragma once
using namespace Microsoft::WRL;

class SQUARE
{
public:
    SQUARE(LPCWSTR filename);
    ~SQUARE();
    void create(LPCWSTR filename);
    void update(const MATRIX& m);
    void draw();
private:
    //頂点バッファとインデックスバッファ
    ComPtr<ID3D12Resource> PositionBuf;
    ComPtr<ID3D12Resource> NormalBuf;
    ComPtr<ID3D12Resource> TexcoordBuf;
    ComPtr<ID3D12Resource> IndexBuf;
    //以下のビューがあれば描画できる
    D3D12_VERTEX_BUFFER_VIEW PositionBufView;
    D3D12_VERTEX_BUFFER_VIEW NormalBufView;
    D3D12_VERTEX_BUFFER_VIEW TexcoordBufView;
    D3D12_INDEX_BUFFER_VIEW IndexBufView;
    //コンスタントバッファ、テクスチャバッファ、ディスクリプタヒープ
    ComPtr<ID3D12Resource> ConstBuf1;
    struct GRAPHIC::CONST_BUF1* ConstBuf1Map;
    ComPtr<ID3D12Resource> ConstBuf2;
    struct GRAPHIC::CONST_BUF2* ConstBuf2Map;
    ComPtr<ID3D12Resource> TextureBuf;
    ComPtr<ID3D12DescriptorHeap> CbvTbvHeap;

};

