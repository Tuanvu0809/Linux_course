# [Observer] Chương trình mô phỏng nhà thông minh. 
# Dựa trên mẫu Observer parten

## 1. Cấu trúc thư mục:

    |--inc
        |----Publisher
            |---- Door.h
            |----smoke.h
        |----Subscriber
            |---- alarm.h
            |---- mobile.h
        |---Publisher.h
        |---Subscriber.h
    |--src
        |----Publisher
            |---- Door.c
            |---- smoke.c
        |----Subscriber
            |---- alarm.c
            |---- mobile.c
        |---Publisher.c
    |-- main.c
    |--Makefile 
    |--Readme.md
# 2.Tổng quan:
- Chương trình mô phỏng một hệ thống nhà thông minh, trong đó:
  -  Các cảm biến (như cảm biến khói và cảm biến cửa) đóng vai trò là **Publisher** (Chủ thể phát sự kiện).
  -  Các thiết bị như chuông báo động hoặc điện thoại là các **Subscriber** (Thiết bị đăng ký nhận sự kiện). 
- Mô hình được triển khai dựa trên Design Pattern "Observer", cho phép các **Subscriber** có thể đăng ký hoặc hủy đăng ký để nhận thông báo khi trạng thái của **Publisher** thay đổi.

# 3. Các thành phần chính:
**Publisher (Phát sự kiện):**

    Door_sensor: cảm biến cửa (mở/đóng).
    Smoke_sensor: cảm biến khói (có khói/không khói).

*Các publisher có khả năng:*

    Quản lý danh sách các subscriber.
    Gửi thông báo khi có sự thay đổi trạng thái.

**Subscriber (Thiết bị nhận sự kiện):**

    Alarm: mô phỏng chuông báo động.
    Mobile: mô phỏng hệ thống điện thoại nhận thông báo.

Mỗi subscriber có thể đăng ký nhận sự kiện từ một hoặc nhiều publisher.

# 4. Diễn biến chương trình chính:
## a.Khởi tạo hệ thống:

Tạo hai publisher: door (cửa), smoke (khói).
Tạo hai subscriber: Alarm_bell, Mobile_phone.

## b. Đăng ký nhận thông báo:

Cả chuông báo và điện thoại đều đăng ký nhận thông báo từ cảm biến cửa và cảm biến khói.

## c.Kích hoạt sự kiện:

Trigger_smoke(&smoke, No_smoke): khởi phát sự kiện không có khói.
Trigger_door(&door, close): mô phỏng cửa đóng.
Trigger_smoke(&smoke, Smoke): mô phỏng phát hiện có khói → tất cả subscriber được thông báo.

## d.Hủy đăng ký:

Chuông báo (Alarm_bell) hủy nhận thông báo từ cảm biến cửa.

## e.Kích hoạt lại sự kiện sau khi hủy đăng ký:

Trigger_door(&door, open): cửa mở → chỉ Mobile_phone được thông báo.
Trigger_smoke(&smoke, Smoke): có khói → cả chuông báo và điện thoại đều được thông báo (vì vẫn còn đăng ký cảm biến khói).

## f. Kết thúc chương trình:
