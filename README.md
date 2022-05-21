# Snake-Game-Project
Game rắn cổ điển được viết bằng ngôn ngữ C++, sử dụng thư viện SDL2.  
## Mục lục  
[Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)  
[Mô tả chung](#mô-tả-chung)  
[Chức năng](#chức-năng)  
[Các kỹ thuật](#các-kỹ-thuật)  
[Kết luận](#kết-luận)  
## Hướng dẫn cài đặt  
  - Tải source code về máy.
  - Mở folder code trong **_VSCode_**.  
  - Mở terminal.
  - Để **chạy game**, sử dụng câu lệnh sau: 
  ```
  mingw32-make && .\main.exe
  ```
## Mô tả chung
  - Ý tưởng: làm lại game rắn săn mồi đồng thời thêm những yếu tố sáng tạo cho game có màu sắc riêng hơn.
  - Snake Game: di chuyển rắn bằng tổ hợp phím mũi tên để rắn ăn quả mà không đâm vào tường, thân mình, chướng ngại vật.
## Chức năng
  - Menu game: [link video demo](https://courses.uet.vnu.edu.vn/)
  - Di chuyển ăn quả cộng điểm: [link video demo](https://courses.uet.vnu.edu.vn/)
  - Rắn đâm vào tường: [link video demo](https://courses.uet.vnu.edu.vn/)
  - Rắn đâm vào chướng ngại vật: [link video demo](https://courses.uet.vnu.edu.vn/)
## Các kỹ thuật
  - Mảng: sử dụng mảng 1 chiều, mảng 2 chiều tĩnh và động.
  - Con trỏ.
  - Lớp.
  - Danh sách liên kết.
  - Đồ hoạ:
      - Âm thanh: sử dụng thư viện SDL_mixer.
      - Hình ảnh: sử dụng thư viện SDL_image, SDL_ttf.
## Kết luận  
  - Hướng phát triển: cập nhật thêm nhiều tính năng mới như:
    - Bảng xếp hạng.
    - Setting chọn chơi lại, loại rắn, bản đồ, chế độ chơi (dễ, khó, góc nhìn),...
    - Thêm các loại quả với các tính năng đặc biệt như: đi xuyên tường, xuyên thân, đi nhanh, cộng nhiều điểm, cộng thêm mạng,...
    - Nhiều level mỗi level rắn sẽ thêm những tính năng mới. Mỗi level sẽ mở thêm bản đồ mới với các loại quả mới, chướng ngại vật mới.
    - Chơi online với nhiều người để giành điểm, bản đồ được mở rộng, các loại quả có sẵn trên bản đồ, người chơi nhập nickname để chơi game. Điều khiển rắn ăn quả, khéo léo cho đầu rắn của đối thủ đâm vào thân rắn của mình thì rắn của đối thủ sẽ chết đồng thời thân rắn của mình sẽ dài thêm bằng độ dài con rắn vừa chết. Sau khi còn lại top 10 sẽ kết thúc game và hiện bảng xếp hạng dựa vào độ dài hiện tại của rắn.
  - Game đã có đủ các chức năng chính của một game rắn cổ điển nhưng cần được phát triển nhiều để hoàn thiện hơn.
  - Sau khi hoàn thiện chương trình em đã học hỏi thêm được rất nhiều về kiến thức và tư duy lập trình với ngôn ngữ C++ như: cách tổ chức chương trình, cách chia file,  cách quản lý các thành phần của game; ngoài ra em còn học được kiến thức để sử dụng thư viện SDL2. Em cảm thấy rất vui và may mắn khi được các thầy hướng dẫn và tạo được một trò chơi mang màu sắc của riêng mình. Nếu có thêm thời gian em sẽ cố gắng phát triển để game hoàn thiện hơn.

 
