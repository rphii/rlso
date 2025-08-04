#include "../src/so.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    So so = SO;
    So_Align al = {0};
    so_al_config(&al, 10, w.ws_col, 0, 1);
    so_extend_al(&so, &al, so("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec non est velit. Interdum et malesuada fames ac ante ipsum primis in faucibus. Nunc id convallis erat. Sed efficitur est ut tempus aliquam. Duis et sodales arcu, id porta urna. Sed porta imperdiet ex, at congue risus imperdiet vitae. Integer auctor ipsum nisl, et viverra magna elementum at. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque nec lobortis odio. Mauris malesuada, nulla ut blandit iaculis, est purus congue lectus, sit amet luctus tellus purus eget nulla. Nam maximus turpis in nisi condimentum commodo. In at leo at nisi semper vestibulum ac ut sapien. Sed eget nibh lacinia, sollicitudin neque a, accumsan sem. Pellentesque ac justo eu orci egestas finibus eget non metus. Donec aliquet mauris id turpis pellentesque suscipit. Aliquam commodo diam nec risus pretium commodo. Nullam ut semper dolor. Aenean eu augue nisl. Suspendisse sit amet libero elementum metus hendrerit condimentum sed vel est. Vestibulum fringilla felis tortor, maximus venenatis mi sollicitudin sit amet. Vestibulum fringilla, enim nec sollicitudin hendrerit, justo velit tempor lacus, vitae lacinia sem felis sit amet orci. Sed fermentum mauris ac lectus facilisis, vitae bibendum nisi consequat. Phasellus nec orci id ligula semper vehicula. Pellentesque eget nibh sapien. Maecenas gravida, mauris at blandit interdum, nisi massa aliquam justo, at ultricies ante felis ut dolor. Ut elit nisi, accumsan sed dignissim nec, elementum consectetur lorem. Pellentesque et consequat orci. Maecenas convallis ac urna ut scelerisque. In quam augue, fringilla quis mattis ut, lobortis quis tortor. Proin vehicula felis vel odio pharetra molestie. Etiam libero ex, ornare vitae posuere volutpat, venenatis eget sapien. Duis tristique odio eget lorem pretium cursus nec quis lorem. Donec scelerisque ultrices neque at commodo. Pellentesque gravida velit sed turpis commodo, in porta tellus molestie. Fusce in velit ac lorem scelerisque imperdiet in eget est. Vivamus vel velit in lorem tincidunt aliquam eu sagittis nibh. Nulla volutpat at justo nec feugiat. Pellentesque sodales vel lacus nec tristique. Maecenas posuere orci dolor, id ultrices quam placerat id. Praesent sem ante, venenatis pellentesque leo ut, laoreet vulputate justo. Fusce in tellus finibus, ultrices ipsum sit amet, eleifend dui. Nulla tincidunt commodo magna, fermentum maximus urna pharetra id. Pellentesque mollis ante tellus, eu efficitur libero hendrerit eu. Donec tempor sem aliquet orci dapibus, nec elementum est bibendum. Donec at mi gravida, finibus dui sit amet, volutpat lacus. Sed enim est, volutpat a est eget, vehicula laoreet arcu. Aenean faucibus venenatis nisi. Vivamus ex justo, congue nec vestibulum posuere, auctor vel dolor. Cras venenatis augue consequat quam porttitor vulputate. Nullam vehicula urna imperdiet, tincidunt felis quis, viverra justo. Nam ullamcorper elit non eleifend aliquam. Nullam cursus, lacus et accumsan volutpat, urna nisi bibendum nisi, a commodo risus justo non mauris. Phasellus eu pulvinar dui. Maecenas et metus justo."));

    so_print(so);
    so_free(&so);

    return 0;
}

