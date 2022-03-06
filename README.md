# "Interactive Wind and Vegetation in 'God of War'" in Unreal Engine 4

This project implement [Interactive Wind and Vegetation in 'God of War'](https://youtu.be/MKX45_riWQA) using Unreal Engine 4

## Implemented features

### Interactive Wind Map ( Using GPU )      
              
RenderTargetTexture is used.     
Convert uv of the renderTargetTexture to location in world space and write wind vector value to texture based on location in world space.         
               
There is three render target texture.              
First one is used by wind maker to write wind vector to render target texture. ( Additive material is used )                     
Second one is used as target texture of post process shading. ( Blur wind map texture, Add static wind vector to wind map )                                  
Thirld one is used for read from vegetation objects. ( Written wind vector is used in vertex shading of vegetation objects ( Tree, Grass.... ) ) ( Double Buffering concept. Texture written by wind maker is read at next frame for performance )                       
         
[Test Video 1](https://youtu.be/OVyJW85vM0E)         

![sdfasdfsaf](https://user-images.githubusercontent.com/33873804/156230627-62c8995b-0788-4e36-b513-bbad49f5cf5d.gif)                
![gifff](https://user-images.githubusercontent.com/33873804/156438399-b6e9e75f-f73f-48f2-bbc5-83ba9268ca47.gif)          
![giffffffffffffffffff](https://user-images.githubusercontent.com/33873804/156440325-9e0acc00-f2c9-4708-996e-5da8482a44cc.gif)              
![sdf](https://user-images.githubusercontent.com/33873804/156938109-b2a92732-5c15-4d0f-b2c6-6e8b4eb2d7ed.gif)            
![sdfdsf](https://user-images.githubusercontent.com/33873804/156938378-a68ceaf3-5ddf-4779-bcc3-9fe5c6713737.gif)              

