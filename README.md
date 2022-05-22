# Snake-Game-Project
Game rắn cổ điển được viết bằng ngôn ngữ C++, sử dụng thư viện SDL2.  
## Mục lục  
[Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)  
[Mô tả chung](#mô-tả-chung)  
[Các chức năng](#các-chức-năng)  
[Các kỹ thuật được sử dụng](#các-kỹ-thuật-được-sử-dụng)  
[Tổng kết](#tổng-kết)  
## Hướng dẫn cài đặt  
  - Tải source code về máy hoặc clone repo về bằng lệnh `git clone https://github.com/lnhi/Snake-Game-Project.git`
  - Mở folder code trong **_VSCode_**.  
  - Mở **terminal**.
  - Để **chạy game**, sử dụng câu lệnh sau: 
  ```
  .\main.exe
  ```
## Mô tả chung
  - **Snake Game**: di chuyển rắn ăn quả để rắn không đâm vào tường, chướng ngại vật hoặc chính nó.
  - **Ý tưởng**: làm lại game rắn săn mồi cổ điển đồng thời thêm những yếu tố sáng tạo cho game có màu sắc riêng hơn:
    - Hình ảnh, âm thanh.
    - Xử lý khúc cua của rắn.
    - Menu.
    - Ghi điểm.
    - Thêm chướng ngại vật. 
    - Rắn chạy nhanh dần.
## Các chức năng
  - Menu, rắn di chuyển ăn quả ghi điểm và đâm vào tường: [link video](https://youtu.be/q0jruWb4gbg)
  - Rắn đâm vào thân mình: [link video](https://youtu.be/4e1W5PPsaAw)
  - Rắn đâm vào chướng ngại vật: [link video](https://youtu.be/G5vfonqVMos)
## Các kỹ thuật được sử dụng
  - **Mảng** 1 chiều, 2 chiều: chủ yếu sử dụng vector để lưu hình ảnh, vị trí của rắn, trạng thái các ô.
  - **Hàng đợi** queue lưu các sự kiện phím của người chơi.
  - **Xử lý chuột:**
    - Bắt phím với `SDL_PollEvent()`
    - `SDL_Event`
  - **Con trỏ**:
    - Truyền địa chỉ 
    - Cấp phát mảng động
  - **Lớp**
    - Lớp `Gallery` để quản lý các ảnh
    - Lớp `PlayGround` quản lý sân chơi
    - Lớp `Snake` có các thuộc tính để quản lý rắn
    - Lớp `Position` chỉ vị trí
    - Lớp `Painter` để vẽ và load ảnh
    - Lớp `Text` tạo chữ lên màn hình
  - **Danh sách liên kết:** lưu các đốt rắn
  - **Đồ hoạ:**
      - Sử dụng thư viện `SDL_mixer.h` để đọc file âm thanh và phát âm thanh nền, âm thanh khi click chuột và khi rắn ăn quả.
      - Sử dụng thư viện `SDL_image.h` để tải ảnh và `SDL_ttf.h` để tải chữ lên màn hình.
  - **Tách file.**
## Tổng kết
1. **Kết luận**: Game đã có đủ các chức năng chính của một game rắn cổ điển và có thêm những yếu tố mới. Code khá dễ hiểu và ngắn gọn tuy nhiên, vẫn còn một số điểm chưa phát triển hết mức có thể nên vẫn cần được hoàn thiện hơn trong tương lai.


2. **Hướng phát triển**: Cải tiến thêm các tính năng chưa có như:
  - Bảng xếp hạng.
  - Bảng setting: _chơi lại, loại rắn, bản đồ, chế độ chơi (dễ, khó, góc nhìn), mức âm thanh.
  - Thêm các loại quả với các tính năng đặc biệt như: _đi xuyên tường, xuyên thân, đi nhanh, cộng nhiều điểm, cộng thêm mạng_,...
  - Nhiều level mỗi level rắn sẽ thêm những tính năng mới. Mỗi level sẽ mở thêm bản đồ mới với các loại quả mới, chướng ngại vật mới.
  - Hai người chơi với màn hình được chia đôi.
  - Chơi online với nhiều người để giành điểm, bản đồ được mở rộng, các loại quả có sẵn trên bản đồ, người chơi nhập nickname để chơi game. Điều khiển rắn ăn quả, khéo léo cho đầu rắn của đối thủ đâm vào thân rắn của mình thì rắn của đối thủ sẽ chết đồng thời thân rắn của mình sẽ dài thêm bằng độ dài con rắn vừa chết. Sau khi còn lại top 10 sẽ kết thúc game và hiện bảng xếp hạng dựa vào độ dài hiện tại của rắn.  

3. **Điều tâm tắc rút ra được sau khi hoàn thiện chương trình:**  
  Sau khi hoàn thiện chương trình em đã học hỏi thêm được rất nhiều về kiến thức và tư duy lập trình với ngôn ngữ C++ như: cách tổ chức chương trình, cách chia file,  cách quản lý các thành phần của game; ngoài ra em còn học được kiến thức để sử dụng thư viện SDL2, cách dùng Github, cách viết file Markdown và rất nhiều điều thú vị nữa. Em cảm thấy rất vui và may mắn khi được các thầy hướng dẫn và tạo được một trò chơi mang màu sắc của riêng mình. Qua đây em thấy làm game không phải là một chuyện dễ dàng và cần người lập trình phải đầu tư rất nhiều thời gian, trí lực. Tuy nhiên nó lại vô cùng thú vị. Nếu có thêm thời gian em sẽ cố gắng phát triển để game hoàn thiện hơn.

 
