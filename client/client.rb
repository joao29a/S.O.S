require 'socket'

def Menu()
    puts("Sistema de Cadastro de Especies de Animais")
    puts("1 - Cadastrar nova especie:")
    puts("2 - Buscar especie: ")
    puts("3 - Remover: ")
    puts("4 - Sair: ")
    opcao = gets.chomp
    if (opcao == "1")
        Cadastrar()
    elsif (opcao == "2")
        Buscar()
    elsif (opcao == "3")
        Remover()
    else
        puts("Goodbye!")
    end
end

def Cadastrar()
    system "clear"
    socket = TCPSocket.new 'localhost', 8888
    puts("Insira o ID da especie: ")
    id = gets.chomp
    puts("Insira o Nome Cientifico da Especie: ")
    nomeCientifico = gets.chomp
    puts("Insira o Nome Popular da Especie: ")
    nomePopular = gets.chomp
    puts("Insira uma breve descricao da Especie: ")
    breveDesc = gets.chomp
    socket.send "cadastrar?id=#{id}&nomeCientifico=#{nomeCientifico}&nomePopular=#{nomePopular}&breveDesc=#{breveDesc}", 0
	resposta = socket.gets
    if (resposta == "status?v=0")
        puts("A especie ja esta cadastrada.")
    elsif (resposta == "status?v=1")
        puts("Cadastro de Especie realizado com sucesso.")
    end
    socket.close
end

def Buscar()
    socket = TCPSocket.new 'localhost', 8888
    puts("Insira uma id para busca: ")
    busca = gets.chomp
    socket.send "buscar?id=#{busca}", 0
    resposta = socket.gets
    if (resposta == "status?v=0")
        puts("Especie nao cadastrada!")
    else
        puts(resposta.split(/&/))
    end
    socket.close
end

def Remover()
    socket = TCPSocket.new 'localhost', 8888
    puts("Insira o id da especie que deseja remover: ")
    remove = gets.chomp
    socket.send "remover?id=#{remove}", 0
	puts(socket.gets)
    socket.close
end

Menu()

