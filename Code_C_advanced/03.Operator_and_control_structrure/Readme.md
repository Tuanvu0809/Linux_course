# Chương trình điều khiển LED Pixel (R-G-B)

- Mô phỏng hoạt động của một thanh pixel (mỗi pixel chứa 3 led đỏ - xanh lá -xanh dương với độ sáng được điều chỉnh để tạo ra các màu khác nhau tùy theo độ sáng của mỗi led).
- Chương trình chính đóng vai trò là người sử dụng khởi tạo ra 1 thanh pixel có độ dài tùy ý.
- Kiểm tra các chức năng được định nghĩ trong file led_driver.c .

## 1. Cấu trúc mã nguồn:

<pre><code>
Operator_and_control_structrure 
  ├──  Main.c
  ├── src 
    ├── led_driver.c
  ├── inc
    ├── led_driver.h
  ├── test
</code></pre>

## 2. Thư viện led_drver.h

- Include các thư viện cần dùng.

      #include <stdio.h>
      #include <stdlib.h>
      #include <stdint.h>

- Các marco.

      #define Max_pixel 32
      #define Green_on_pixel 8
      #define Red_on_pixel 16
      #define Blue_on_pixel 0

- Các hàm.

      int led_init(size_t num_pixels);
      const uint32_t\* led_get_Buffer();
      size_t led_get_pixel_count();


      void led_printf_index(size_t index);
      void led_shutdown();
      void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
      void led_fill(uint8_t r, uint8_t g, uint8_t b);
      void led_clear();

## 3. Các hàm trong led_driver.c

- Biến toàn cục và chỉ được sử dụng trong file chứa mảng led và số lượng led khởi tạo:

  - Khởi tạo một con trỏ uint32_t có giá trị là Null và 1 biến kiểu size_t để lấy giá trị được khởi tạo từ file main.

    - Giá trị là uint32_t để lưu trũ dữ liệu của 1 pixel(Mỗi pixel LED được điều khiển bởi một giá trị 32-bit uint32_t để dễ dàng thao tác. Tuy nhiên, chỉ 24 bit được sử dụng để chứa dữ liệu màu).

            [8-bits] | [8-bits] | [8-bits] |[8-bits]
            [Not used] | [Red] | [Green] | [Blue]

    - Giá trị size_t sẽ tự động có độ lớn phù hợp với kiến trúc hệ thống (32-bit hay 64-bit). Để chứa số Pixel mà người dùng cần khởi tạo.

        static uint32_t \*Led_arr = NULL;
        static size_t Led_quantity = 0;

- Hàm **Led_init**:

          int led_init(size_t num_pixels){
                Led_arr = (uint32_t *) malloc(num_pixels * sizeof(uint32_t));
                if(Led_arr == NULL || num_pixels >Max_pixel )
                    return -1;
                Led_quantity = num_pixels ;
                led_clear();
                    return 0;
          }

  - Khởi tạo mảng led bằng cách cấp phát động cho con trỏ Led_arr với số lượng biến uint32_t bằng num_pixel.
  - Kiểm tra khởi tạo con trỏ Led_arr. Nếu không tạo được mảng sẽ trả về giá trị -1 và kết thúc hàm, nều tạo thành công ta tiến hành gán giá trị num_pixel cho Led_quantity và set tất cả các led về màu đen bằng hàm led_clear được định nghĩa sau.

- Hàm **led_shutdown**:

            void led_shutdown()
            {
                free(Led_arr);
                Led_quantity = 0;
                Led_arr = NULL;
            }

  - Giải phóng dung lượng con trỏ Led_arr trong vùng nhớ heap khi kết thúc chương trình và đặt các giá trị về mặc định.

- Hàm **led_set_pixel_color**:

        void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b){
            if(Led_arr == NULL || (index >= led_get_pixel_count() || index < 0)) return;

            Led_arr[index] = ((uint32_t) g<<Green_on_pixel) | ((uint32_t) r<<Red_on_pixel) | ((uint32_t) b<<Blue_on_pixel);
        }

  - Chọn màu cho pixel index. Nếu Led_arr bằng NULL thì sẽ kết thúc hàm, nếu Led_arr không bằng NULL thì sẽ set màu cho mỗi led tùy theo set up 3 màu(RGB) và dịch các bit theo các marco được định nghĩa sẵn.

- Hàm **led_get_Buffer**:

        const uint32_t* led_get_Buffer(){
            return Led_arr;
        }

  - Trả về Led_arr nếu các file khác cần sử dụng.

- Hàm **led_get_pixel_count**:.

        size_t led_get_pixel_count(){
             return Led_quantity;
        }

  - Trả về Led_quantity nếu các file khác cần sử dụng.

-Hàm **led_fill**:

     void led_fill(uint8_t r, uint8_t g, uint8_t b){

     uint32_t *calculate = (uint32_t *) malloc(sizeof(uint32_t));
    if(calculate == NULL)       return;
    *calculate = ((uint32_t) g<<Green_on_pixel) | ((uint32_t) r<<Red_on_pixel) | ((uint32_t) b<<Blue_on_pixel);

        for(size_t i=0; i<led_get_pixel_count();i++)
        {
            Led_arr[i] = *calculate;
        }
    free(calculate);
    }

- Tính toán giá trị R-G-B và gán giá trị đó cho toàn bộ pixel.

-Hàm **led_clear**:

    void led_clear()
    {
        led_fill(0,0,0);
    }

- Gán gán giá trị đó cho toàn bộ pixel là tắt.
  -Hàm **led_printf_index**:

      void led_printf_index(size_t index){
          if(Led_arr == NULL || (index >= led_get_pixel_count() || index <0)) return;

          printf("Pixel  %2d = 0x%p\n",index,Led_arr[index]);
      }

  - Kiểm tra pixel theo Index có bật đúng hay không, nếu giá trị được kiểm tra vượt qua số lượng pixel được khởi tạo thì sẽ trả về và thoát khỏi hàm.

## 4. Chương trình chính:

- #### Khởi tạo một dải LED với 10 pixel bằng led_init(10).
- #### Kiểm tra xem buffer có được khởi tạo về 0 hết không.
- #### Đặt màu cho pixel đầu tiên (index 0) thành màu Đỏ (255, 0, 0).
- #### Đặt màu cho pixel cuối cùng (index 9) thành màu Xanh dương (0, 0, 255).
- #### Đặt màu cho một pixel ở giữa (ví dụ: index 4) thành màu Trắng (255, 255, 255).
- #### Sử dụng hàm led_get_buffer() để lấy con trỏ tới buffer dữ liệu.
- #### In ra giá trị hexa của các pixel tại index 0, 4, và 9 để xác thực gọi hàm led_printf_index().
  - Giá trị tại index 0 phải là 0x0000FF00 (Red).
  - Giá trị tại index 9 phải là 0x000000FF (Blue).
  - Giá trị tại index 4 phải là 0x00FFFFFF (White).
- #### Gọi hàm led_fill() để đặt tất cả các pixel thành màu Xanh lá (0, 255, 0).
- #### Kiểm tra lại buffer để đảm bảo tất cả 10 pixel đều có giá trị 0x00FF0000.
- #### Gọi led_shutdown() để giải phóng bộ nhớ.
