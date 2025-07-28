#  Mô tả về State Machine (Máy Trạng Thái)
## 1. Khái niệm
State Machine là một mô hình lập trình trong đó một hệ thống có thể ở một trong nhiều trạng thái khác nhau tại một thời điểm, và hành vi của nó thay đổi tùy theo trạng thái hiện tại.

Mỗi trạng thái định nghĩa một tập hợp các hành động hợp lệ và có thể dẫn đến chuyển đổi sang trạng thái khác khi một sự kiện xảy ra.

## 2. Thành phần chính
**Thành phần**	
 - State (Trạng thái):	Đại diện cho một tình huống cụ thể mà hệ thống đang ở trong đó tại một thời điểm (ví dụ: Stopped, Playing, Paused trong trình phát nhạc).
- Event (Sự kiện):Tác động bên ngoài hoặc hành động người dùng (ví dụ: nhấn nút Play, Stop, Pause).
- Transition (Chuyển trạng thái):	Quá trình chuyển từ trạng thái này sang trạng thái khác do sự kiện gây ra.
- Action (Hành động):	Hành vi được thực hiện khi một sự kiện xảy ra trong trạng thái hiện tại (có thể trước hoặc sau khi chuyển trạng thái).
- Context (Ngữ cảnh):	Đối tượng trung tâm chứa trạng thái hiện tại và chuyển đổi qua các trạng thái khác (ví dụ: lớp MusicPlayer).

## 3. Cách hoạt động
**Quy trình của một State Machine có thể mô tả như sau:** 

- Hệ thống khởi tạo ở một trạng thái ban đầu.
- Khi một sự kiện xảy ra (vd: người dùng bấm nút), hệ thống sẽ:
- Kiểm tra trạng thái hiện tại.
- Thực hiện hành động tương ứng nếu có.
- Chuyển sang trạng thái mới nếu có quy định chuyển.
- Vòng lặp tiếp tục mỗi khi có sự kiện mới.



## 4. Ví dụ thực tế: Trình phát nhạc
Trình phát nhạc có 3 trạng thái:

***Stopped***

***Playing***

***Paused***

Hành vi của nút Play, Pause, Stop sẽ khác nhau tùy trạng thái.
→ Đây là ứng dụng thực tế điển hình của State Machine.

## 5. Biểu diễn bằng sơ đồ (State Diagram)

[Stopped] → (Play) → [Playing] → (Pause) → [Paused]
    ↑                         ↓ (Stop)        ↓ (Stop)
    +-------------------------+---------------+