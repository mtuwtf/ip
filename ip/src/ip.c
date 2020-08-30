/*
 * $Id: $
 *
 * Copyright (c) 2020 Mark T. Uemura <mtu@me.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdarg.h>    /* va_list */
#include <unistd.h>    /* ssize_t */

#include <stddef.h>    /* NULL */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <stdio.h>

#include <kcgi.h>
#include <kcgihtml.h>

int 
main(void)
{
	struct kreq 	r;
	struct khead	*p;
	 
	enum krequ requ;
	 
	const char     *page = "index";
	 
	if (KCGI_OK != khttp_parse(&r, NULL, 0, &page, 1, 0))
		return(EXIT_FAILURE);
		  
	if (-1 == pledge("stdio", NULL)) {
		perror("pledge");
		khttp_free(&r);
		return(EXIT_FAILURE);
	}
	 
	khttp_head(&r, kresps[KRESP_STATUS],          "%s", khttps[KHTTP_200]);
   	khttp_head(&r, kresps[KRESP_ALLOW],           "OPTIONS POST");
   	khttp_head(&r, kresps[KRESP_CACHE_CONTROL],   "no-cache, no-store, must-revalidate");
   	khttp_head(&r, kresps[KRESP_PRAGMA],          "no-cache");
   	khttp_head(&r, kresps[KRESP_CONTENT_TYPE],    "%s", kmimetypes[r.mime]);
	khttp_head(&r, kresps[KRESP_X_FRAME_OPTIONS], "DENY");
	 
   	khttp_head(&r, "X-Content-Type-Options", "nosniff");
   	khttp_head(&r, "X-XSS-Protection", "1; mode=block");
	 
	khttp_body(&r);
	khttp_puts(&r, "<!DOCTYPE html><title>ip</title>");
	 
	khttp_puts(&r, "<body alink=\"#7e7e7e\" background=\" data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEASABIAAD/2wBDAAMCAgICAgMCAgIDAwMDBAYEBAQEBAgGBgUGCQgKCgkICQkKDA8MCgsOCwkJDRENDg8QEBEQCgwSExIQEw8QEBD/2wBDAQMDAwQDBAgEBAgQCwkLEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBD/wAARCAAIB6gDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREAAgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRChYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD3eMAHGa0bbHHNFFfyrQVmf0vW2NOD+taNt0xRRXtYaTR4tc0bYexrStznbg9qKK93DvY8bEGnbZxWlD1HNFFe9QdrHiVzRtiPWtK3Oehoor3sOeRXRpwfd7VowdP8+1FFe5QPErmjb9PxqeiivYp/CeVPcKKKKskKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKACiiigAooooAKKKKAP//Z\" bgcolor=\"#ffffff\" link=\"#990099\" vlink=\"#7e7e7e\">");
	khttp_puts(&r, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">");
	 
   	khttp_puts(&r, "<div style=\"padding:15px;text-align:center;\">");
	 
	khttp_puts(&r, "<table>");
	khttp_puts(&r, "<tr><td>Current IP Address: ");
	khttp_puts(&r, "</td>");
	khttp_puts(&r, "<td>");
	 
	if ((r.remote)) {
		khttp_puts(&r, r.remote);
	}
	 
	khttp_puts(&r, "</td></tr>");
	khttp_puts(&r, "</table>");
	 
	khttp_puts(&r, "</div>");
	 
	khttp_puts(&r, "</body>");
	khttp_puts(&r, "</html>");
	 
	khttp_free(&r);
	return (EXIT_SUCCESS);
}
