/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <student@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../framework/bonus/libunit_bonus.h"
#else
# include "../framework/mandatory/libunit.h"
#endif

/*
** Launcher prototipleri — her fonksiyon 00_launcher.c dosyasında tanımlanır.
**
** Bir launcher'ı devre dışı bırakmak için:
**   Fonksiyon çağrısını yorum satırına al.
**   Prototip satırına dokunma.
*/
int	dummy_tests_launcher(void);

/*
** main — Tüm test launcher'larını sırayla çağıran giriş noktası.
**
** Sorumlulukları:
**   - Her launcher'ı çağırmak
**   - İstenilen launcher'ı yorum satırıyla devre dışı bırakabilmek
**   - Genel başarı/başarısızlık durumunu döndürmek
**
** Not: Launcher'ların kendisi launch_tests() çağırır ve sonuç döndürür.
**      Bu fonksiyonda satir limiti norm kurallarina
**      tabi degildir.
*/
int	main(void)
{
	dummy_tests_launcher();
	return (0);
}
