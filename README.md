# Snake-Game-Project
Game rắn cổ điển được code bằng c++, sử dụng thư viện SDL2.  
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
  - Rắn đâm vào tường chết: [link video demo](https://courses.uet.vnu.edu.vn/)
  - Rắn đâm vào chướng ngại vật chết: [link video demo](https://courses.uet.vnu.edu.vn/)
## Các kỹ thuật
  - Mảng: sử dụng mảng 1 chiều, mảng 2 chiều tĩnh và động.
  - Con trỏ.
  - Class.
  - Danh sách liên kết.
  - Đồ hoạ:
      - Âm thanh: sử dụng thư viện SDL_mixer
      - Hình ảnh: sử dụng thư viện SDL_image, SDL_ttf
## Hướng phát triển
  - Cập nhật thêm nhiều tính năng mới như:
    - Bảng xếp hạng.
    - Setting chọn rắn, quả, map, chế độ.
    - Thêm các loại quả với các tính năng đặc biệt.
    - Mở rộng nhiều map với nhiều chướng ngại vật khác nhau.
    - Nhiều level mỗi level rắn sẽ thêm những tính năng mới: xuyên tường, xuyên mình,...
## Kết luận
  - Đánh giá: Game đã có đủ các chức năng chính của một game rắn cổ điển nhưng cần được phát triển nhiều hơn nữa. 
  - Sau khi hoàn thiện chương trình em đã học hỏi thêm được rất nhiều về kiến thức và tư duy lập trình với ngôn ngữ C++ như: cách tổ chức chương trình, cách chia file,  cách quản lý các thành phần của game; ngoài ra còn có kiến thức để sử dụng thư viện SDL2 và nhiều điều bổ ích nữa. Nếu có thêm thời gian em sẽ cố gắng phát triển để game hoàn thiện hơn.

 
