#include <stdio.h>

int main() {
    int num_orders;
    int valid_order_count = 0;
    int error_order_count = 0;
    double total_shift_revenue = 0.0;
    double max_order_value = 0.0;
    int security_breach = 0;

    // Nhập tổng số đơn hàng trong ca
    if (scanf("%d", &num_orders) != 1) {
        return 1;
    }

    // Lớp phòng thủ 3: Ca làm việc trống hoặc dữ liệu không hợp lệ
    if (num_orders <= 0) {
        printf("--- BAO CAO CHOT SO CA LAM VIEC ---\n");
        printf("Tong so don hang hop le: 0\n");
        printf("Tong so don hang loi/huy: 0\n");
        printf("Tong doanh thu ca: 0.00 VND\n");
        printf("Don hang co gia tri lon nhat: 0.00 VND\n");
        return 0;
    }

    // Vòng lặp for duyệt từng hóa đơn trong ca
    for (int i = 1; i <= num_orders; i++) {
        double base_price;
        char size_type;
        int topping_count;
        int is_member;

        // Nhập liệu giao dịch
        if (scanf("%lf %c %d %d", &base_price, &size_type, &topping_count, &is_member) != 4) {
            error_order_count++;
            continue;
        }

        // Lớp phòng thủ 2: Phát hiện gian lận / Tín hiệu ngắt khẩn cấp khi topping âm
        if (topping_count < 0) {
            security_breach = 1;
            break;
        }

        // Lớp phòng thủ 1: Kiểm tra lỗi cú pháp giá cơ sở và ký tự size
        if (base_price <= 0 || (size_type != 'S' && size_type != 's' && 
                                 size_type != 'M' && size_type != 'm' && 
                                 size_type != 'L' && size_type != 'l')) {
            error_order_count++;
            continue;
        }

        // Tính toán phụ thu Size
        double current_order_total = base_price;
        if (size_type == 'M' || size_type == 'm') {
            current_order_total += 6000.0;
        } else if (size_type == 'L' || size_type == 'l') {
            current_order_total += 10000.0;
        }

        // Phụ thu Topping (8000 VNĐ mỗi phần)
        current_order_total += topping_count * 8000.0;

        // Ưu đãi Hội viên Vàng (Giảm 10% nếu is_member == 1)
        if (is_member == 1) {
            current_order_total = current_order_total * 0.9;
        }

        // Cập nhật thống kê ca làm việc
        valid_order_count++;
        total_shift_revenue += current_order_total;

        if (current_order_total > max_order_value) {
            max_order_value = current_order_total;
        }
    }

    // Xuất báo cáo tổng kết cuối ca
    printf("--- BAO CAO CHOT SO CA LAM VIEC ---\n");
    if (security_breach == 1) {
        printf("CANH BAO: He thong phat hien gian lận/su co (Topping am)! Da ngat ca lam viec dot ngot.\n");
    }
    printf("Tong so don hang hop le: %d\n", valid_order_count);
    printf("Tong so don hang loi/huy: %d\n", error_order_count);
    printf("Tong doanh thu ca: %.2f VND\n", total_shift_revenue);
    printf("Don hang co gia tri lon nhat: %.2f VND\n", max_order_value);

    return 0;
}
