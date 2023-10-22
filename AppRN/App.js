import { StatusBar } from 'expo-status-bar';
import { useState } from 'react';
import { StyleSheet, TextInput,Image, Text, View, ScrollView, Button, Switch} from 'react-native';

export default function App() {
  const [acceptedTerms, setAcceptedTerms] = useState(false);
  const [email, setEmail] = useState('');
  const [contra, setContra] = useState('');

  const handleCreateAccount = () => {
    if(email == ''){
      alert('Introduzca el email')
    }else if(contra == ''){
      alert('Introduzca la contraseña')
    }else{
      alert('Bienvenido ' + email)
    }
    
  };

  return (
    <View style={styles.container}>
      <Text>Bienvenido a Practica 3 React Native</Text>
      <StatusBar style="auto" />
      <Image source={require('./assets/icon.png')} style={{ width: 150, height: 150 }} />

      <Text>Email:</Text>
      <TextInput style={styles.input} placeholder="Introduce tu correo electrónico" 
      keyboardType="email-address" onChangeText={text => setEmail(text)}/>

      <Text>Contraseña</Text>
      <TextInput style={styles.input} placeholder="Introduce tu Contraseña" 
      secureTextEntry onChangeText={text => setContra(text)}/>

      <Text style={styles.boldText}>Términos de uso</Text>
      <View style={styles.scrollContainer}>
        <ScrollView style={styles.ScrollView}>
          <Text>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut interdum varius tellus vitae consequat. 
                            Sed ut nibh vestibulum, tincidunt sem at, maximus elit. Vestibulum eget semper dui. In eu neque in nisi faucibus
                            dapibus. Proin eu dui dignissim, consectetur urna non, gravida felis. Fusce rhoncus, arcu eget dapibus tristique,
                            est sem feugiat risus, et scelerisque nisl diam vel mauris. Quisque efficitur pellentesque ante, et suscipit mi posuere
                              nec. Suspendisse potenti. Mauris pellentesque velit sed urna gravida, nec fringilla enim fringilla.
                            Phasellus dapibus leo nec risus posuere, id viverra orci aliquet. Sed auctor iaculis ligula at dignissim. Maecenas vitae
                            libero non purus ultrices interdum nec a neque. Fusce consectetur semper ligula, ac dapibus tellus euismod id. 
                            Suspendisse eget malesuada lectus. Nulla facilisi. Nulla vel lorem fringilla, varius ipsum id, pharetra ex. Donec 
                            id varius elit, sed tristique lorem. Vivamus pulvinar massa enim, non lobortis lectus sagittis in.
          </Text>
          <Text style={styles.boldText}>Aceptar términos de uso:</Text>
          <Switch value={acceptedTerms} onValueChange={value => setAcceptedTerms(value)} />
    
        </ScrollView>
      </View>

      <Button title="Crear cuenta" onPress={handleCreateAccount} disabled={!acceptedTerms}/>

    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  scrollContainer: {
    width: '40%',
    height: '150px',
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',

  },
  boldText: {
    fontWeight: 'bold',
    margin: 10,
  },
  input:{
    width: '20%',
    height: 40,
    margin: 10,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 10,
    paddingHorizontal: 10,
    borderRadius: 5,
  },
  ScrollView: {
    width: '100%',
    paddingHorizontal: 20,
  },

});


