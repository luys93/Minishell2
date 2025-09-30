/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:50 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:25:51 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	quando trova una parola, la scorre finche non trova un carattere
	non adatto, dopo aver salvato le posizioni della parola all'interno
	della stringa, salva la parola isolandola e la aggiunde alla lista */
int	split_word(t_data *data, int i, int *pos)
{
	int		start;
	char	*word;
	int		len;
	t_token	*token;

	start = i;
	while (data->input[i] && !is_space(data->input[i])
		&& !is_delimiter(data->input[i]) && !is_quotes(data->input[i])
		&& !is_double_quotes(data->input[i]))
		i++;
	len = i - start;
	word = ft_strndup(&data->input[start], len);
	token = add_token_to_list(data, word, WORD, '\0');
	if (data->input[i] && !is_space(data->input[i])
		&& !is_delimiter(data->input[i]))
		token->must_joined = 1;
	*pos = i;
	return (0);
}

/*	quando troviamo un " -o- ' dobbiamo fare un controllo importante,
	prima di salvare il contenuto all'interno, si controlla se siano
	chiuse correttamente, dopo aver fatto il controllo, possiamo isolare
	il contenuto e aggiungerlo alla lista */
int	split_quote(t_data *data, int i, int *pos)
{
	char	quote_type;
	int		start;
	char	*quotes;
	t_token	*token;

	if (data->input[i] == '\'' || data->input[i] == '"')
		quote_type = data->input[i];
	start = ++i;
	while (data->input[i] && data->input[i] != quote_type)
		i++;
	if (split_word_error(pos, data, i) == 1)
		return (1);
	if ((i - start) == 0)
		quotes = ft_strdup("");
	else
		quotes = ft_strndup(&data->input[start], i - start);
	token = add_token_to_list(data, quotes, QUOTED, quote_type);
	if (data->input[i] == quote_type)
		i++;
	if (data->input[i] && !is_space(data->input[i])
		&& !is_delimiter(data->input[i + 1]))
		token->must_joined = 1;
	*pos = i;
	return (0);
}

/*	quando trova un metachar, verifica che sia 1 o 2 in base a cosa trova
	esempi: << = 2, | = 1, > = 1
	dopo aver verificato questa cosa,
		isola il carattere e lo aggiunge alla lista */
int	split_metachar(t_data *data, int i, int *pos)
{
	int		len;
	char	*metachar;
	t_token	*token;

	len = is_match(&data->input[i]);
	if (len == 0)
	{
		i += 1;
		*pos = i;
		return (1);
	}
	metachar = ft_strndup(&data->input[i], len);
	token = add_token_to_list(data, metachar, METACHAR, '\0');
	if (!token)
		return (1);
	*pos = i + len;
	return (0);
}

/*	qui individuiamo i token principali: se "eof", "quotes",
	"metachar", "spazio" o "parola" */
int	detect_token(t_data *data, int i)
{
	if (!data->input[i])
		return (T_EOF);
	if (data->input[i] == '\'' || data->input[i] == '"')
		return (T_QUOTES);
	if (is_delimiter(data->input[i]))
		return (T_METACHAR);
	if (is_space(data->input[i]))
		return (T_SKIP);
	return (T_WORDS);
}

/*	qui inzia il processo di tokenizer, scorrendo l'input di
	carattere in carattere, in base a cosa troviamo facciamo uno split
	dedicato, se e una parola trova la fine o se trova un metacarattere
	vede se e composto da 2 caratteri o uno solo */

int	tokenizer(t_data *data)
{
	int		i;
	int		condition;
	//t_token	*last_token;

	i = 0;
	//last_token = NULL;
	while (data->input[i])
	{
		condition = detect_token(data, i);
		if (condition == T_SKIP)
			i++;
		else if (condition == T_METACHAR)
		{
			if (split_metachar(data, i, &i) == 1)
				return (1);
		}
		else if (condition == T_QUOTES)
		{
			if (split_quote(data, i, &i) == 1)
				return (1);
		}
		else if (condition == T_WORDS)
			split_word(data, i, &i);
	}
	return (0);
}
