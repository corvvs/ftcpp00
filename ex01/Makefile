CXX			:=	clang++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -D BUILD42=1
NAME		:=	phonebook
SRCS		:=	main.cpp PhoneBook.cpp Contact.cpp Utils.cpp
OBJS		:=	$(SRCS:.cpp=.o)

.PHONY		:	all clean fclean re

all			:	$(NAME)
$(NAME)		:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)


clean		:
	$(RM) -rf $(OBJS)

fclean		:	clean
	$(RM) $(NAME)

re			:	fclean all
